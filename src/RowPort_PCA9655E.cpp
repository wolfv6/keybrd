#include "RowPort_PCA9655E.h"

/*
configures column port's configuration and output.
*/
RowPort_PCA9655E::RowPort_PCA9655E(IOExpanderPort& port)
    : port(port), configurationByteCommand(port.num + 6), outputByteCommand(port.num + 2)
{}

void RowPort_PCA9655E::begin()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(configurationByteCommand);
    Wire.write(0);                              //0=configure as output (for strobe pins and LED)
    Wire.endTransmission();
}

/*
sets activePin pin output to low, does not reset the other pins because they might be used by LEDs.
activePin is port mask, where active pin is 1.
*/
void RowPort_PCA9655E::setActivePinLow(const uint8_t activePin)
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(outputByteCommand);
    Wire.write(port.outputVal &= ~activePin);
    Wire.endTransmission();
}

/*
sets activePin pin output to high.
activePin is port mask, where active pin is 1.
*/
void RowPort_PCA9655E::setActivePinHigh(const uint8_t activePin)
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(outputByteCommand);
    Wire.write(port.outputVal |= activePin);
    Wire.endTransmission();
    //todo delayMicroseconds(1500); still 4*bb w/o debouncer prints IOE rows sporadically
}
