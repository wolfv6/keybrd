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
Scanner_uC::Scanner_uC(const bool strobeOn, const uint8_t readPins[], const uint8_t readPinCount)
    : strobeOn(strobeOn), strobeOff(!strobeOn), readPins(readPins), readPinCount(readPinCount)
{
    uint8_t mode;

    //configure read pins
    if (strobeOn == LOW)                        //if active low
    {
        mode = INPUT_PULLUP;                    //use internal pull-up resistor
    }
    else                                        //if active high
    {
        mode = INPUT;                           //requires external pull-down resistor
    }

    for (uint8_t i=0; i < readPinCount; i++)
    {
        pinMode(readPins[i], mode);
    }
}

/* init() is called once for each row from Row constructor.
Configure row-strobe pin to output.
*/
void Scanner_uC::init(const uint8_t strobePin)
{
    pinMode(strobePin, OUTPUT);
}

/* scan() is called on every iteration of sketch loop().
scan() strobes the row's strobePin and retuns state of readPins.
Bit patterns are 1 bit per key.
*/
read_pins_t Scanner_uC::scan(const uint8_t strobePin)
{
    read_pins_t readState = 0;                  //bits, 1 means key is pressed, 0 means released
    read_pins_t readMask = 1;                   //bits, active bit is 1

    //strobe row on
    digitalWrite(strobePin, strobeOn);
    delayMicroseconds(3);                       //time to stablize voltage

    //read all the read pins
    for (uint8_t i=0; i < readPinCount; i++)
    {
        if ( digitalRead(readPins[i]) == strobeOn )
        {
            readState |= readMask;
        }
        readMask <<= 1;
    }

    //strobe row off
    digitalWrite(strobePin, strobeOff);

    return readState;
}
