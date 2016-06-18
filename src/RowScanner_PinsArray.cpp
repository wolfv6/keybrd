#include "RowScanner_PinsArray.h"

/* constructor
*/
RowScanner_PinsArray::RowScanner_PinsArray(const uint8_t strobePin,
        const uint8_t readPins[], const uint8_t READ_PIN_COUNT)
    : strobePin(strobePin), readPins(readPins), READ_PIN_COUNT(READ_PIN_COUNT)
{
    uint8_t mode;

    //configure row
    pinMode(strobePin, OUTPUT);

    if (activeHigh)
    {
        mode = INPUT;                   //requires external pull-down resistor
    }
    else
    {
        mode = INPUT_PULLUP;            //uses internal pull-up resistor
    }

    //configure cols
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        pinMode(readPins[i], mode);
    }
}

/* scan() Strobes the row and reads the columns.
Sets rowEnd and returns rowState.
rowEnd is a bitwise row mask, one col per bit, where active col bit is 1.
At end of function, 1 bit marks place immediatly after last key of row.
rowEnd is a larger type than portMask so that it can not overflow.

https://www.arduino.cc/en/Tutorial/DigitalPins
https://www.arduino.cc/en/Reference/PinMode
https://www.arduino.cc/en/Reference/DigitalWrite
https://www.arduino.cc/en/Reference/DigitalRead
https://www.arduino.cc/en/Reference/Constants > Digital Pins modes: INPUT, INPUT_PULLUP, and OUTPUT
*/
uint8_t RowScanner_PinsArray::scan(uint16_t& rowEnd)
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

    //read all the column pins
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
