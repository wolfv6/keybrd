#include "ColPort_PCA9655E.h"

/*
configures column port's configuration, input, and pins.
*/
ColPort_PCA9655E::ColPort_PCA9655E
(IOExpanderPort& port, const uint8_t colPins)
    : ColPort(colPins), port(port), configurationByteCommand(port.num + 6), inputByteCommand(port.num)
{}

void ColPort_PCA9655E::begin()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(configurationByteCommand);
    Wire.write(colPins);    //0=configure as output (for LED), 1=configure as input (for read)
    Wire.endTransmission();
}

/*
Saves all port-pin values to portState.
*/
void ColPort_PCA9655E::read()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(inputByteCommand);               //input immediately before requestFrom
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(port.ADDR, 1u);            //request one byte from input port

    portState = Wire.read();
}
