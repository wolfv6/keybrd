#include "LED_MCP23018.h"

void LED_MCP23018::on()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(GPIO);
    Wire.write(port.outputVal &= ~pin);           //set pin low (sink)
    Wire.endTransmission();
}

void LED_MCP23018::off()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(GPIO);
    Wire.write(port.outputVal |= pin);            //set pin high (sink off)
    Wire.endTransmission();
}
