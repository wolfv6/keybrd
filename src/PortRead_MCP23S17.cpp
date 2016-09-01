#include "PortRead_MCP23S17.h"

/*
PortRead_MCP23S17::begin() is not needed because port direction is already configured to input by default.
SPI bus is configured in PortWrite_MCP23S17::begin().
*/

/*
returns port value
*/
uint8_t PortRead_MCP23S17::read()
{
    uint8_t portState;                  //bit wise

    //slower clock
    digitalWrite(SS, LOW);              //enable Slave Select
      SPI.transfer(port.ADDR << 1 | 1); //read command
      SPI.transfer(port.num + 0x12);    //register address to read data from
      portState = SPI.transfer(0);      //save the data (0 is dummy data to send)
    digitalWrite(SS, HIGH);             //disable Slave Select

    return portState;
}
