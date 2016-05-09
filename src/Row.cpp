#include "Row.h"
/*
scans the row and calls any newly pressed or released keys.
*/
void Row::process(const bool activeHigh)
{
    //these variables are all bitwise, one bit per key
    uint8_t rowState;                           //1 means pressed, 0 means released
    uint16_t rowEnd;                            //1 bit marks positioned after last key of row
    uint8_t newDebounced;                       //1 means pressed, 0 means released
    uint8_t isFallingEdge;                      //1 means falling edge
    uint8_t isRisingEdge;                       //1 means rising edge

    scan(activeHigh);                           //save column-port-pin values to portState
    rowState = getRowState(rowEnd, activeHigh);
    newDebounced = debounce(rowState);
    detectEdge(newDebounced, isFallingEdge, isRisingEdge);
    pressRelease(rowEnd, isFallingEdge, isRisingEdge);
}

/*
Strobes the row and reads the columns.
Strobe is on for shortest possible time to preserve IR LED on DodoHand's optic switch.
*/
void Row::scan(const bool activeHigh)
{
    //strobe row on
    if (activeHigh)
    {
        refRowPort.setActivePinHigh(rowPin);
    }
    else //activeLow
    {
        refRowPort.setActivePinLow(rowPin);
    }

    //read all the column ports
    for (uint8_t i=0; i < colPortCount; i++)
    {
        ptrsColPorts[i]->read();
    }

    //strobe row off
    if (activeHigh)
    {
        refRowPort.setActivePinLow(rowPin);
    }
    else //activeLow
    {
        refRowPort.setActivePinHigh(rowPin);
    }
}

/*
Copies column pins to rowState.  Unused column pins are not copied.
Sets rowEnd and returns rowState.
rowEnd is bitwise, where 1 bit corrsiponds to place immediatly after last key of row.
rowEnd and rowMask are larger type than portMask so that they can not overflow.
*/
uint8_t Row::getRowState(uint16_t& rowEnd, const bool activeHigh)
{
    uint16_t rowMask = 1;           //bitwise, one col per bit, active col bit is 1
    uint8_t rowState = 0;           //bitwise, one key per bit, 1 means key is pressed

    for (uint8_t i=0; i < colPortCount; i++)    //for each col port
    {
        //bitwise colPins, 1 means pin is connected to column
        uint8_t colPins = ptrsColPorts[i]->getColPins();

        //bitwise colPortState, pin values where set in ColPort::read(), get them now
        uint8_t colPortState = ptrsColPorts[i]->getPortState();

        if (activeHigh)
        {
            colPortState = ~colPortState;
        }

        for ( uint8_t portMask = 1; portMask > 0; portMask <<= 1 ) //shift portMask until overflow
        {                                       //for each pin of col port
            if (portMask & colPins)             //if pin is connected to column
            {
                if (portMask & ~colPortState)   //if pin detected a key press
                {
                    rowState |= rowMask;        //set rowState bit for that key
                }

                rowMask <<= 1;                  //shift rowMask to next key
            }
        }
    }

    rowEnd = rowMask;

    return rowState;
}

/*
Parameter rowState is bitwise, 1 means pressed, 0 means released.
Returns debounced rowState.

Debounce uses multiple samples to debounces switch states,
where each sample contains the switch states for a row of keys, one bit per switch.

Debounce uses Marty's debounce algorithm from
 http://drmarty.blogspot.com.br/2009/05/best-switch-debounce-routine-ever.html
I2C and TWI protocals do not include any Packet Error Checking (PEC).
The goal of Marty's debounce routine is to reject spurious signals,
which is useful when conecting split keyboards with a cable using I2C or TWI.
Was tested on split keyboard with 3-meter long telephone wire to I/O expander

Marty's debounce algorithm:
 Periodically read samples and update the state when a number consecutive sample bits are equal.

samples[SAMPLE_COUNT] is a ring buffer and samplesIndex is it's current write index.
SAMPLE_COUNT is #defined in Row.h
SAMPLE_COUNT is the number of consecutive equal samples needed to debounce.
It is a macro because it is used to define array size of samples[SAMPLE_COUNT] in Row.
SAMPLE_COUNT should be at lease 2.

Multiple samples are for error correction on I2C I/O expander and shorten response time.
On keyboards without I/O expander, multiple samples only shorten response time.
Larger SAMPLE_COUNTs are more reliable but consume more memory, where
     SAMPLE_COUNT*ROW_COUNT = bytes of memory consumed by keyboard
So don't make SAMPLE_COUNT too large, SAMPLE_COUNT = 4 is very reliable for I2C error correction.

big SAMPLE_COUNT for fast response, small SAMPLE_COUNT to save memory
there is a way to define SAMPLE_COUNT in the sketch, but it's ugly
 see http://forum.arduino.cc/index.php?topic=364843.0 > rely #2
*/
uint8_t Row::debounce(const uint8_t rowState)
{
    uint8_t all_1 = ~0;                         //bitwise
    uint8_t all_0 = 0;                          //bitwise

    delayMicroseconds(DELAY_MICROSECONDS);      //delay between Row scans to debounce key

    samples[samplesIndex] = rowState;           //insert rowState into samples[] ring buffer

    if (++samplesIndex >= SAMPLE_COUNT)
    {
        samplesIndex = 0;                       //wrap samplesIndex to beginning of ring buffer
    }

    for (uint8_t j = 0; j < SAMPLE_COUNT; j++)  //traverse the sample[] ring buffer
    {
        all_1 &= samples[j];                    //1 if all samples are 1
        all_0 |= samples[j];                    //0 if all samples are 0
    }

    // update newDebounce if all the samples agree with one another
    // if all samples=1 then newDebounced=1
    //     elseif all samples=0 then newDebounced=0
    //         else newDebounced=debounced i.e. no change
    return all_1 | (all_0 & debounced);
}

/*
Computes isFallingEdge and isRisingEdge.
All 3 parameters are bitwise.
*/
void Row::detectEdge(uint8_t newDebounced, uint8_t& isFallingEdge, uint8_t& isRisingEdge)
{
    uint8_t debouncedChanged;                   //bitwise

    debouncedChanged = newDebounced xor debounced;
    debounced = newDebounced;

    //bit=1 if last debounced changed from 1 to 0, else bit=0
    isFallingEdge = debouncedChanged & ~debounced;

    //bit=1 if last debounced changed from 0 to 1, else bit=0
    isRisingEdge = debouncedChanged & debounced;
}

/*
calls key's press() or release() function if it was pressed or released.
All 3 parameters are bitwise.
*/
void Row::pressRelease(const uint16_t rowEnd, const uint8_t isFallingEdge,
                       const uint8_t isRisingEdge)
{
    uint8_t rowMask;                            //bitwise, active col bit is 1
    uint8_t col;                                //index for ptrsKeys[col] array

    for (rowMask=1, col=0; rowMask<rowEnd; rowMask<<=1, col++) //for each key in row
    {
        //release before press avoids impossible key sequence
        if (rowMask & isFallingEdge)            //if key was released
        {
            ptrsKeys[col]->release();
        }

        if (rowMask & isRisingEdge)             //if key was pressed
        {
            ptrsKeys[col]->press();
            keyWasPressed();
        }
    }
}
            
void Row::keyWasPressed()
{
    //empty in Row class.  To unstick sticky keys, override keyWasPressed() in derived class.
}
