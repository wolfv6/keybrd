#include "RowScanner_PinsBitwise.h"
/*
Strobes the row and reads the columns.
Sets rowEnd and returns rowState.
*/
read_pins_t RowScanner_PinsBitwise::scan(read_pins_mask_t& rowEnd)
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

    //read the port pins
    refColPort.read();

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
uint8_t RowScanner_PinsBitwise::getRowState(read_pins_mask_t& rowEnd)
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

    return rowState;
}
