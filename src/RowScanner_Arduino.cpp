#include "RowScanner_Arduino.h"

/*
Strobes the row and reads the columns.
Sets rowEnd and returns rowState.
rowEnd is a bitwise row mask, one col per bit, where active col bit is 1.
At end of function, 1 bit marks place immediatly after last key of row.
rowEnd is a larger type than portMask so that it can not overflow.
*/
uint8_t RowScanner_Arduino::scan(uint16_t& rowEnd)
{
    uint8_t rowState = 0;
    rowEnd = 1;

    //strobe row on
    if (activeHigh)
    {
        digitalWrite(strobePin, HIGH);
    }
    else //activeLow
    {
        digitalWrite(strobePin, LOW);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column ports
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        if ( digitalRead(readPins[i]) == activeHigh )
        {
            rowState |= rowEnd;
        }
        rowEnd <<= 1;
    }

    //strobe row off
    if (activeHigh)
    {
        digitalWrite(strobePin, LOW);
    }
    else //activeLow
    {
        digitalWrite(strobePin, HIGH);
    }

    return rowState;
}
