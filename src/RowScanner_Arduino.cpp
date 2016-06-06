#include "RowScanner_Arduino.h"
/*
Strobes the row and reads the columns.
Strobe is on for shortest possible time to preserve IR LED on DodoHand's optic switch.
*/
uint8_t RowScanner_Arduino::scan(uint16_t& rowEnd)
{
    uint8_t rowState = 0;

    //strobe row on
    if (activeHigh)
    {
        digitalWrite(0, HIGH);
    }
    else //activeLow
    {
        digitalWrite(0, LOW);
    }
    delayMicroseconds(3);  //time to stablize voltage
    
/*
    uint8_t col = 1;

    //read all the column ports
    for (uint8_t i=0; i < readPinCount; i++)
    {
        if (digitalRead(6))
        {
            rowState |= col;
            //ptrsColPorts[i]->read();
        }
        col <<= 1;
    }
*/
        if (digitalRead(6) == 0)
        {
            rowState |= 1<<0;
        }
        if (digitalRead(7) == 0)
        {
            rowState |= 1<<1;
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

Keyboard.print(rowState); // prints 2b, not 1a,  what happened to col0?
    return rowState;
}
