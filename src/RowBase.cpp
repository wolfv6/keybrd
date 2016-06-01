#include "RowBase.h"
/*
scans the row and calls any newly pressed or released keys.
*/
void RowBase::process(const bool activeHigh)
{
    //these variables are all bitwise, one bit per key
    uint8_t rowState;                           //1 means pressed, 0 means released
    uint16_t rowEnd;                            //1 bit marks positioned after last key of row
    uint8_t debounced;                       //1 means pressed, 0 means released
    uint8_t isFallingEdge;                      //1 means falling edge
    uint8_t isRisingEdge;                       //1 means rising edge

    scan(activeHigh);                           //save column-port-pin values to portState
    rowState = getRowState(rowEnd, activeHigh);
    debounced = debounce(rowState);
    detectEdge(debounced, isFallingEdge, isRisingEdge);
    pressRelease(rowEnd, isFallingEdge, isRisingEdge);
}

/*
Strobes the row and reads the columns.
Strobe is on for shortest possible time to preserve IR LED on DodoHand's optic switch.
*/
void RowBase::scan(const bool activeHigh)
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
uint8_t RowBase::getRowState(uint16_t& rowEnd, const bool activeHigh)
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
Computes isFallingEdge and isRisingEdge.
All 3 parameters are bitwise.
*/
void RowBase::detectEdge(uint8_t debounced, uint8_t& isFallingEdge, uint8_t& isRisingEdge)
{
    uint8_t debouncedChanged;                   //bitwise

    debouncedChanged = debounced xor previousDebounced;
    previousDebounced = debounced;

    //bit=1 if last debounced changed from 1 to 0, else bit=0
    isFallingEdge = debouncedChanged & ~previousDebounced;

    //bit=1 if last debounced changed from 0 to 1, else bit=0
    isRisingEdge = debouncedChanged & previousDebounced;
}

/*
calls key's press() or release() function if it was pressed or released.
All 3 parameters are bitwise.
*/
void RowBase::pressRelease(const uint16_t rowEnd, const uint8_t isFallingEdge,
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
            
void RowBase::keyWasPressed()
{
    //empty in RowBase class.  To unstick sticky keys, override keyWasPressed() in derived class.
}
