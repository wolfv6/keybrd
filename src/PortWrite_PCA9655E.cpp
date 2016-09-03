#include "PortWrite_PCA9655E.h"

/*
If PortRead_PCA9655E is instantiated on the same port, do NOT use PortWrite_PCA9655E::begin().
Otherwise readPins could be overwritten.
*/
void PortWrite_PCA9655E::begin()
{
    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 6);                   //configuration byte command
    Wire.write(0);                              //0=configure as output (for strobe pins and LED)
    Wire.endTransmission();
}

/*
pin is bitwise, where pin being strobed is 1.
value is HIGH or LOW.
Does not reset the other pins because LEDs could be using some of the pins.
Syntax is similar to Arduino DigitalWrite().
*/
void PortWrite_PCA9655E::write(const uint8_t pin, const bool value)
{
    if (value == LOW)                           //if active low
    {
        port.outputVal &= ~pin;                 //set pin output to low
    }
    else                                        //if active high
    {
        port.outputVal |= pin;                  //set pin output to high
    }

    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 2);                   //output Byte command
    Wire.write(port.outputVal);
    Wire.endTransmission();
}
