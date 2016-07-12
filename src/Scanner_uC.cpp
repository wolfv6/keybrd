#include "Scanner_uC.h"

/* constructor
*/
Scanner_uC::Scanner_uC(const uint8_t STROBE_PIN,
        const uint8_t READ_PINS[], const uint8_t READ_PIN_COUNT)
    : STROBE_PIN(STROBE_PIN), READ_PINS(READ_PINS), READ_PIN_COUNT(READ_PIN_COUNT)
{
    uint8_t mode;

    //configure row
    pinMode(STROBE_PIN, OUTPUT);

    if (STROBE_ON == LOW)               //if active low
    {
        mode = INPUT_PULLUP;            //uses internal pull-up resistor
    }
    else
    {
        mode = INPUT;                   //requires external pull-down resistor
    }

    //configure read pins
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        pinMode(READ_PINS[i], mode);
    }
}

/* scan() Strobes the row and reads the columns.
Sets READ_PIN_COUNT and returns rowState.

https://www.arduino.cc/en/Tutorial/DigitalPins
https://www.arduino.cc/en/Reference/PinMode
https://www.arduino.cc/en/Reference/DigitalWrite
https://www.arduino.cc/en/Reference/DigitalRead
https://www.arduino.cc/en/Reference/Constants > Digital Pins modes: INPUT, INPUT_PULLUP, and OUTPUT
*/
read_pins_t Scanner_uC::scan(uint8_t& readPinCount)
{
    read_pins_t rowState = 0;                   //bitwise, one col per bit, 1 means key is pressed
    read_pins_t readMask = 1;                   //bitwise, one col per bit, active col bit is 1

    //strobe row on
    digitalWrite(STROBE_PIN, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the read pins
    for (uint8_t i=0; i < READ_PIN_COUNT; i++)
    {
        if ( digitalRead(READ_PINS[i]) == STROBE_ON )
        {
            rowState |= readMask;
        }
        readMask <<= 1;
    }

    //strobe row off
    digitalWrite(STROBE_PIN, STROBE_OFF);

    readPinCount = READ_PIN_COUNT;
    return rowState;
}
