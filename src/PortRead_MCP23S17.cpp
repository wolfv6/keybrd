#include "PortRead_MCP23S17.h"

/* begin() is called from Scanner_IOE::begin().
Configures port to to read (input with pullup enabled).
*/
void PortRead_MCP23S17::begin(const uint8_t strobeOn)
{
    if (strobeOn == LOW)                        //if active low
    {
        pullUp = readPins;
    }
    else
    {
        pullUp = 0;
    }

    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1);      //write command
      SPI.transfer(port.num);                   //configure IODIR
      SPI.transfer(readPins);                   //0=output (for LED), 1=input (for read)
    digitalWrite(SS, HIGH);                     //enable Slave Select

    digitalWrite(SS, LOW);                      //disable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1);      //write command
      SPI.transfer(port.num + 0x0C);            //configure GPPU
      SPI.transfer(pullUp);                     //0=pull-up disabled (for LED), 1=pull-up enabled (for read)
    digitalWrite(SS, HIGH);                     //disable Slave Select
}

/* read() returns portState.
Only portState bits of readPins are valid.
*/
uint8_t PortRead_MCP23S17::read()
{
    uint8_t portState;                          //bit wise

    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer( (port.DEVICE_ADDR << 1) | 1); //read command
      SPI.transfer(port.num + 0x12);            //GPIO register address to read data from
      portState = SPI.transfer(0);              //save the data (0 is dummy data to send)
    digitalWrite(SS, HIGH);                     //disable Slave Select

    return portState;
}
