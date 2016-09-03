#include "PortRead_MCP23S17.h"

/*
SPI bus is configured in PortWrite_MCP23S17::begin().
*/
void PortRead_MCP23S17::begin(const uint8_t strobeOn)
{
    uint8_t pullUp;                             //bitwise, 1 means internal pull-up resistor enabled

    if (strobeOn == LOW)                        //if active low
    {
        pullUp = readPins;
    }
    else
    {
        pullUp = 0;
    }

    pinMode(SS, OUTPUT);                        //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);                     //disable Slave Select
    SPI.begin();
    SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //control SPI bus todo is slow clock needed?

    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1);             //write command
      SPI.transfer(port.num);                   //configure IODIR
      SPI.transfer(readPins);                   //0=output (for LED), 1=input (for read)
    digitalWrite(SS, LOW);                      //enable Slave Select

    digitalWrite(SS, HIGH);                     //disable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1);             //write command
      SPI.transfer(port.num + 0x0C);            //configure GPPU
      SPI.transfer(pullUp);                     //0=pull-up disabled (for LED), 1=pull-up enabled (for read)
    digitalWrite(SS, HIGH);                     //disable Slave Select

    //SPI.endTransaction() is not called to release the SPI bus
    // because keyboard only has one SPI device.
}

/*
read() returns portState.
*/
uint8_t PortRead_MCP23S17::read()
{
    uint8_t portState;                          //bit wise

    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1 | 1);         //read command
      SPI.transfer(port.num + 0x12);            //GPIO register address to read data from
      portState = SPI.transfer(0);              //save the data (0 is dummy data to send)
    digitalWrite(SS, HIGH);                     //disable Slave Select

    return portState;
}
