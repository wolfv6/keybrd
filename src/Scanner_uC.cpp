#include "Scanner_uC.h"

/* Scanner_uC functions call Arduino's Digital Pins functions
https://www.arduino.cc/en/Tutorial/DigitalPins
https://www.arduino.cc/en/Reference/PinMode
https://www.arduino.cc/en/Reference/DigitalWrite
https://www.arduino.cc/en/Reference/DigitalRead
https://www.arduino.cc/en/Reference/Constants > Digital Pins modes: INPUT, INPUT_PULLUP, and OUTPUT
*/

/* constructor
*/
Scanner_uC::Scanner_uC(const uint8_t strobePin,
        const uint8_t readPins[], const uint8_t readPinCount)
    : strobePin(strobePin), readPins(readPins), readPinCount(readPinCount)
{
    uint8_t mode;

    //configure row
    pinMode(strobePin, OUTPUT);

    if (STROBE_ON == LOW)               //if active low
    {
        mode = INPUT_PULLUP;            //use internal pull-up resistor
    }
    else                                //if active high
    {
        mode = INPUT;                   //requires external pull-down resistor
    }

    //configure read pins
    for (uint8_t i=0; i < readPinCount; i++)
    {
        pinMode(readPins[i], mode);
    }
}

/* scan() strobes the row's strobePin and retuns state of readPins.
Bitwise variables are 1 bit per key.
*/
read_pins_t Scanner_uC::scan()
{
    read_pins_t readState = 0;                  //bitwise, 1 means key is pressed, 0 means released
    read_pins_t readMask = 1;                   //bitwise, active bit is 1

    //strobe row on
    digitalWrite(strobePin, STROBE_ON);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the read pins
    for (uint8_t i=0; i < readPinCount; i++)
    {
        if ( digitalRead(readPins[i]) == STROBE_ON )
        {
            readState |= readMask;
        }
        readMask <<= 1;
    }

    //strobe row off
    digitalWrite(strobePin, STROBE_OFF);

    return readState;
}
