#include "PortWrite_MCP23S17.h"

/* writePort() sets registerAddr to data.
*/
void PortWrite_MCP23S17::writePort(const uint8_t registerAddr, const uint8_t data)
{
    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(port.ADDR << 1);             //write command
      SPI.transfer(registerAddr);               //register address to write data to
      SPI.transfer(data);                       //data
    digitalWrite(SS, HIGH);                     //disable Slave Select
}    

/* begin() should be called once from sketch in setup().
PortRead_MCP23S17 and PortWrite_MCP23S17 should be on seperate ports on the same MCP23S17.
Output pins can be used for strobe pins and LEDs.
*/
void PortWrite_MCP23S17::begin()
{
    pinMode(SS, OUTPUT);                        //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);                     //disable Slave Select
    SPI.begin();
    SPI.beginTransaction(SPISettings (SPI_CLOCK_DIV8, MSBFIRST, SPI_MODE0)); //control SPI bus todo is slow clock needed?

    writePort(port.num, 0);                     //configure port direction (port.num) to output (0)

    //SPI.endTransaction() is not called to release the SPI bus
    // because keyboard only has one SPI device.
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
