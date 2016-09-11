#include "PortRead_PCA9655E.h"

/*
*/
void PortRead_PCA9655E::begin(const uint8_t strobeOn)
{
    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 6);                   //configuration byte command
    Wire.write(readPins);    //0=configure as output (for LED), 1=configure as input (for read)
    Wire.endTransmission();
}

/*
returns port value
*/
uint8_t PortRead_PCA9655E::read()
{
    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num);                       //input byte command
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(port.DEVICE_ADDR, 1u);     //request one byte from input port

    return Wire.read();
}
