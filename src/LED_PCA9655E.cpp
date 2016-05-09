#include "LED_PCA9655E.h"

void LED_PCA9655E::on()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(outputByteCommand);
    Wire.write(port.outputVal |= pin);            //set pin high
    Wire.endTransmission();
}

void LED_PCA9655E::off()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(outputByteCommand);
    Wire.write(port.outputVal &= ~pin);           //set pin low
    Wire.endTransmission();
}
