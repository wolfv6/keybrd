#include "PortRead_PCA9655E.h"

/* begin() is called from Scanner_IOE::begin().
Configures port to to read (input).
*/
void PortRead_PCA9655E::begin(const uint8_t strobeOn)
{
    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 6);                   //configuration byte command
    Wire.write(readPins);                       //0=output (for LED), 1=input (for read)
    Wire.endTransmission();
}

/* read() returns portState.
Only portState bits of readPins are valid.
*/
uint8_t PortRead_PCA9655E::read()
{
    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num);                       //input byte command
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(port.DEVICE_ADDR, 1u);     //request one byte from input port

    return Wire.read();
}
