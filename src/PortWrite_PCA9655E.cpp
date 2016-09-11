#include "PortWrite_PCA9655E.h"

/*
If PortRead_PCA9655E is instantiated on the same port, do NOT use PortWrite_PCA9655E::begin().
Otherwise readPins could be overwritten.
*/
void PortWrite_PCA9655E::begin()
{
    Wire.begin();

    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 6);                   //configuration byte command
    Wire.write(0);                              //0=configure as output (for strobe pins and LED)
    Wire.endTransmission();
}

/*
strobePin is bitwise, where pin being strobed is 1.
pinLogicLevel is HIGH or LOW.
Does not reset the other pins because LEDs could be using some of the pins.
Syntax is similar to Arduino DigitalWrite().
*/
void PortWrite_PCA9655E::write(const uint8_t strobePin, const bool pinLogicLevel)
{
    if (pinLogicLevel == LOW)                   //if strobePin low
    {
        port.outputVal &= ~strobePin;           //set pin output to low
    }
    else                                        //if strobestrobe high
    {
        port.outputVal |= strobePin;            //set pin output to high
    }

    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 2);                   //output Byte command
    Wire.write(port.outputVal);
    Wire.endTransmission();
}
