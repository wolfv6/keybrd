#include "PortRead_MCP23S17.h"

/* begin() is called from Scanner_IOE::begin().
Configures read pins to input with pullup enabled.
*/
void PortRead_MCP23S17::begin(const uint8_t strobeOn)
{
    if (strobeOn == LOW)                        //if active low
    {
        pullUp = readPins;
    }
    else                                        //active high requires external pull-down resistors
    {
        pullUp = 0;
    }

    transfer(port.DEVICE_ADDR << 1, port.num, readPins); //write, configure IODIR, 0=output, 1=input
    transfer(port.DEVICE_ADDR << 1, port.num + 0x0C, pullUp); //write, configure GPPU,
                                                          //0=pull-up disabled, 1=pull-up enabled
}

/* read() returns portState.
Only portState bits of readPins are valid.
*/
uint8_t PortRead_MCP23S17::read()
{
    return transfer( (port.DEVICE_ADDR << 1) | 1, port.num + 0x12, 0); //read from GPIO
}
