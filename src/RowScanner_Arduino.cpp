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
        digitalWrite(stobePin, HIGH);
    }
    else //activeLow
    {
        digitalWrite(stobePin, LOW);
    }
    delayMicroseconds(3);  //time to stablize voltage
    
    //read all the column ports
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        if ( digitalRead(readPins[i]) == activeHigh )
        {
            rowState |= col;
        }
/*
Keyboard.print(" stobePin");
Keyboard.print(stobePin);
Keyboard.print(" readPins[");
Keyboard.print(i);
Keyboard.print("]");
Keyboard.print((int)readPins[i]);
Keyboard.print(" col");
Keyboard.print(col);
Keyboard.print(" ");
*/
        col <<= 1;
    }

    //strobe row off
    if (activeHigh)
    {
        digitalWrite(0, LOW);
    }
    else //activeLow
    {
        digitalWrite(0, HIGH);
    }
   
    rowEnd = 4; //only read first two col, a1 b2 4

//Keyboard.print(rowState);
    return rowState;
}
