#include "RowPort_MCP23018.h"

/*
configures column port's IODIR, GPIO.
*/
RowPort_MCP23018::RowPort_MCP23018(IOExpanderPort& port)
    : port(port), IODIR(port.num), GPIO(port.num + 0x12)
{}

void RowPort_MCP23018::begin()
{
//Wire.begin() should only be called once https://www.arduino.cc/en/Reference/WireBegin
#ifndef WIRE_BEGIN
#define WIRE_BEGIN
    Wire.begin();
#endif

    Wire.beginTransmission(port.ADDR);
    Wire.write(IODIR);
    Wire.write(0);                            //0=configure as output (for strobe pins and LED pins)
    Wire.endTransmission();
}

/*
sets activePin pin output to low.
activePin is port mask, where active-low pin is 1.
*/
void RowPort_MCP23018::setActivePinLow(const uint8_t activePin)
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(GPIO);
    Wire.write(port.outputVal &= ~activePin);
    Wire.endTransmission();
}

/*
sets activePin pin output to high, does not reset the other pins because they might be used by LEDs.
activePin is port mask, where active-high pin is 1.
*/
void RowPort_MCP23018::setActivePinHigh(const uint8_t activePin)
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(GPIO);
    Wire.write(port.outputVal |= activePin);
    Wire.endTransmission();
}
