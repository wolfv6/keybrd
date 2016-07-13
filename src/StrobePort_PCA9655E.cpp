#include "StrobePort_PCA9655E.h"

/*
configures column port's configuration and output.
*/
StrobePort_PCA9655E::StrobePort_PCA9655E(IOEPort& port)
    : port(port), configurationByteCommand(port.num + 6), outputByteCommand(port.num + 2) {}

void StrobePort_PCA9655E::begin()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(configurationByteCommand);
    Wire.write(0);                              //0=configure as output (for strobe pins and LED)
    Wire.endTransmission();
}

/*
pin is bitwise, where pin being strobed is 1.
value is HIGH or LOW.
Does not reset the other pins because LEDs could be using some of the pins.
*/
void StrobePort_PCA9655E::write(const uint8_t pin, const bool value)
{
    if (value == LOW)                           //if active low
    {
        port.outputVal &= ~pin;                 //set pin output to low
    }
    else                                        //if active high
    {
        port.outputVal |= pin;                  //set pin output to high
    }

    Wire.beginTransmission(port.ADDR);
    Wire.write(outputByteCommand);
    Wire.write(port.outputVal);
    Wire.endTransmission();
}
