#include "RowScanner_Arduino.h"

/*
Strobes the row and reads the columns.
*/
uint8_t RowScanner_Arduino::scan(uint16_t& rowEnd)
{
    uint8_t rowState = 0;
    uint8_t col = 1;

    //strobe row on
    if (activeHigh)
    {
        digitalWrite(strobePin, HIGH);
    }
    else //activeLow
    {
        digitalWrite(strobePin, LOW);
    }
    delayMicroseconds(3);  //time to stablize voltage

    //read all the column ports
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        if ( digitalRead(readPins[i]) == activeHigh )
        {
            rowState |= col;
        }
        col <<= 1;
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
   
    rowEnd = col;
    return rowState;
}
