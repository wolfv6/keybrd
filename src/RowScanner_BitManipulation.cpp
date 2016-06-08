#include "RowScanner_BitManipulation.h"
/*
Strobes the row and reads the columns.
Strobe is on for shortest possible time to preserve IR LED on DodoHand's optic switch.
*/
uint8_t RowScanner_BitManipulation::scan(uint16_t& rowEnd)
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
   
    return getRowState(rowEnd);
}

/*
Copies column pins to rowState.  Unused column pins are not copied.
Sets rowEnd and returns rowState.
rowEnd is a bitwise row mask, one col per bit, where active col bit is 1.
At end of function, 1 bit marks place immediatly after last key of row.
rowEnd is a larger type than portMask so that it can not overflow.
*/
uint8_t RowScanner_BitManipulation::getRowState(uint16_t& rowEnd)
{
    uint8_t rowState = 0;           //bitwise, one key per bit, 1 means key is pressed

    rowEnd = 1;

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
                    rowState |= rowEnd;         //set rowState bit for that key
                }

                rowEnd <<= 1;                   //shift rowEnd to next key
            }
        }
    }

    return rowState;
}
