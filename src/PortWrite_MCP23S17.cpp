#include "PortWrite_MCP23S17.h"

void PortWrite_MCP23S17::writePort(const uint8_t registerAddr, const uint8_t data)
{
    //slower clock
    //SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //control SPI bus todo move to begin()
    digitalWrite(SS, LOW);              //enable Slave Select
      SPI.transfer(port.ADDR << 1);     //write command
      SPI.transfer(registerAddr);       //register address to write data to
      SPI.transfer(data);               //data
    digitalWrite(SS, HIGH);             //disable Slave Select
    //SPI.endTransaction();               //release the SPI bus
}    

/*
If PortRead_MCP23S17 is instantiated on the same port, do NOT use PortWrite_MCP23S17::begin().
Otherwise readPins could be overwritten.
Output pins can be used for strobe pins and LEDs.

SPI.endTransaction() is not called because keyboard only has one SPI device, so no need to release the SPI bus
*/
void PortWrite_MCP23S17::begin()
{
    pinMode(SS, OUTPUT);                //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);             //disable Slave Select
    SPI.begin();
    SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //control SPI bus

    writePort(port.num, 0);             //configure port direction (port.num) to output (0)
}

/*
pin is bitwise, where pin being strobed is 1.
strobe is HIGH or LOW (for active high or active low).
port.outputVal can be shared by LEDs.
The functions does not reset the other pins so that they can be used for LEDs.
*/
void PortWrite_MCP23S17::write(const uint8_t pin, const bool strobe)
{
    if (strobe == LOW)                          //if active low
    {
        port.outputVal &= ~pin;                 //set pin output to low
    }
    else                                        //if active high
    {
        port.outputVal |= pin;                  //set pin output to high
    }

    writePort(port.num + 0x12, port.outputVal);  //set GPIO port pins for stobe and LEDs
}
