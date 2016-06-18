#include "ColPort_MCP23018.h"

/*
configures column port's IODIR, GPIO, and GPPU.
*/
ColPort_MCP23018::ColPort_MCP23018(IOExpanderPort& port, const uint8_t colPins)
    : ColPort(colPins), port(port), IODIR(port.num), GPIO(port.num + 0x12), GPPU(port.num + 0x0C)
{}

void ColPort_MCP23018::begin(uint8_t activeHigh)
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(IODIR);
    Wire.write(colPins);        //0=configure as output (for LED), 1=configure as input (for read)
    Wire.endTransmission();

    Wire.beginTransmission(port.ADDR);
    Wire.write(GPPU);
    if (activeHigh)
    {
        Wire.write(0);          //0=pull-up disabled for activeHigh //todo not tested yet
    }
    else
    {
        Wire.write(colPins);    //0=pull-up disabled (for LED), 1=pull-up enabled (for read)
    }
    Wire.endTransmission();
}

/*
Saves all port-pin values to portState.
*/
void ColPort_MCP23018::read()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(GPIO);                           //GPIO immediately before requestFrom
    Wire.endTransmission();

    Wire.requestFrom(port.ADDR, 1u);            //request one byte from input port

    portState = Wire.read();
}
