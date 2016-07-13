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
level is HIGH or LOW.
*/
void StrobePort_PCA9655E::write(const uint8_t pin, const bool level)
{
    if (level == LOW)
    {
        port.outputVal &= ~pin; //set pin output to low, do not reset the other pins because LEDs
    }
    else 
    {
        port.outputVal |= pin; //set pin output to high
    }

    Wire.beginTransmission(port.ADDR);
    Wire.write(outputByteCommand);
    Wire.write(port.outputVal);
    Wire.endTransmission();
}
