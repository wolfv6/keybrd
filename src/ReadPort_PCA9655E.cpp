#include "ReadPort_PCA9655E.h"

/*
configures column port's configuration, input, and pins.
*/
ReadPort_PCA9655E::ReadPort_PCA9655E (IOEPort& port, const uint8_t readPins)
    : ReadPort(readPins), port(port), configurationByteCommand(port.num + 6), inputByteCommand(port.num)
{}

void ReadPort_PCA9655E::begin()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(configurationByteCommand);
    Wire.write(readPins);    //0=configure as output (for LED), 1=configure as input (for read)
    Wire.endTransmission();
}

/*
Saves all port-pin values to portState.
*/
void ReadPort_PCA9655E::read()
{
    Wire.beginTransmission(port.ADDR);
    Wire.write(inputByteCommand);               //input immediately before requestFrom
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(port.ADDR, 1u);            //request one byte from input port

    portState = Wire.read();
}
