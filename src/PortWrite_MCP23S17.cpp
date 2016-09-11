#include "PortWrite_MCP23S17.h"

/* writePort() sets registerAddr to data.
*/
void PortWrite_MCP23S17::writePort(const uint8_t registerAddr, const uint8_t data)
{
    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1);      //write command
      SPI.transfer(registerAddr);               //register address to write data to
      SPI.transfer(data);                       //data
    digitalWrite(SS, HIGH);                     //disable Slave Select
}    

/* begin() is called from Scanner_IOE::begin().  Initiates SPI bus and configures write pins.
PortRead_MCP23S17 and PortWrite_MCP23S17 should be on seperate ports on the same MCP23S17.
Output pins can be used for strobe pins and LEDs.
*/
void PortWrite_MCP23S17::begin()
{
    pinMode(SS, OUTPUT);                        //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);                     //disable Slave Select
    SPI.begin();
    SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //control SPI bus todo is slow clock needed?
    //SPI.endTransaction() not called to release SPI bus because keyboard only has one SPI device.

    writePort(port.num, 0);                     //configure port direction (port.num) to output (0)
}

/*
strobePin is bitwise, where pin being strobed is 1.
pinLogicLevel is HIGH or LOW.
port.outputVal can be shared by LEDs.
The function does not reset the other pins so that they can be used for LEDs.
*/
void PortWrite_MCP23S17::write(const uint8_t strobePin, const bool pinLogicLevel)
{
    if (pinLogicLevel == LOW)
    {
        port.outputVal &= ~strobePin;           //set strobePin output to low
    }
    else
    {
        port.outputVal |= strobePin;            //set strobePin output to high
    }

    writePort(port.num + 0x12, port.outputVal); //set GPIO port pins for strobe and LEDs
}
