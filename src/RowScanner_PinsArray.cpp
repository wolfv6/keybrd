#include "RowScanner_PinsArray.h"

/* constructor
*/
RowScanner_PinsArray::RowScanner_PinsArray(const uint8_t STROBE_PIN,
        const uint8_t READ_PINS[], const uint8_t READ_PIN_COUNT)
    : STROBE_PIN(STROBE_PIN), READ_PINS(READ_PINS), READ_PIN_COUNT(READ_PIN_COUNT)
{
    uint8_t mode;

    //configure row
    pinMode(STROBE_PIN, OUTPUT);

    if (ACTIVE_HIGH)
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
        pinMode(READ_PINS[i], mode);
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
read_pins_t RowScanner_PinsArray::scan(read_pins_mask_t& rowEnd)
{
    read_pins_t rowState = 0;                   //bitwise
    rowEnd = 1;

    //strobe row on
    if (ACTIVE_HIGH)
    {
        digitalWrite(STROBE_PIN, HIGH);
    }
    else //activeLow
    {
        digitalWrite(STROBE_PIN, LOW);
    }
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the column pins
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        if ( digitalRead(READ_PINS[i]) == ACTIVE_HIGH )
        {
            rowState |= rowEnd;
        }
        rowEnd <<= 1;
    }

    //strobe row off
    if (ACTIVE_HIGH)
    {
        digitalWrite(STROBE_PIN, LOW);
    }
    else //activeLow
    {
        digitalWrite(STROBE_PIN, HIGH);
    }

    return rowState;
}
