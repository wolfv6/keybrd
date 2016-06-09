#include "RowScanner_PinsBitwise.h"
/*
Strobes the row and reads the columns.
Strobe is on for shortest possible time to preserve IR LED on DodoHand's optic switch.
*/
uint8_t RowScanner_PinsBitwise::scan(uint16_t& rowEnd)
{
    //strobe row on
    if (activeHigh)
    {
        refRowPort.setActivePinHigh(strobePin);
    }
    else //activeLow
    {
        refRowPort.setActivePinLow(strobePin);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the port pins
    refColPort.read();
/* shows strobing pin 1 and 2, but realy stobing 0 and 1 todo
Keyboard.print(F(" strobePin="));
Keyboard.print(strobePin);
Keyboard.print(F(", "));
*/
    //strobe row off
    if (activeHigh)
    {
        refRowPort.setActivePinLow(strobePin);
    }
    else //activeLow
    {
        refRowPort.setActivePinHigh(strobePin);
    }
   
    return getRowState(rowEnd);
}

/*
Copies column pins to rowState.  Unused column pins are not copied.
Sets rowEnd and returns rowState.
rowEnd is a bitwise row mask, one col per bit, where active col bit is 1.
At end of function, 1 bit marks place immediatly after last key of row.
rowEnd is a larger type than portMask so that it can not overflow.
*/
uint8_t RowScanner_PinsBitwise::getRowState(uint16_t& rowEnd)
{
    uint8_t rowState = 0;           //bitwise, one key per bit, 1 means key is pressed
    uint8_t portMask;               //bitwise, 1 bit is a colPortState position

    rowEnd = 1;

    //bitwise colPins, 1 means pin is connected to column
    uint8_t colPins = refColPort.getColPins();

    //bitwise colPortState, pin values where set in ColPort::read(), get them now
    uint8_t colPortState = refColPort.getPortState();

    if (activeHigh)
    {
        colPortState = ~colPortState;
    }

    for ( portMask = 1; portMask > 0; portMask <<= 1 ) //shift portMask until overflow
    {                                       //for each pin of col port
        if (portMask & colPins)             //if pin is connected to column
        {
            if (portMask & ~colPortState)   //if pin detected a key press
            {
                rowState |= rowEnd;         //set rowState bit for that key
            }

            rowEnd <<= 1;                   //shift rowEnd to next key
        }
    }
//todo Keyboard.print(rowState);

    return rowState;
}
