#include "PortWrite_MCP23S17.h"

/* push() writes data to registerAddr.
*/
void PortWrite_MCP23S17::push(const uint8_t registerAddr, const uint8_t data)
{
    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(port.DEVICE_ADDR << 1);      //write command
      SPI.transfer(registerAddr);               //register address to write data to
      SPI.transfer(data);                       //write the data
    digitalWrite(SS, HIGH);                     //disable Slave Select
}    

/* begin() is called from Scanner_IOE::begin().
Initiates SPI bus and configures write pins to output.
MCP23S17 SPI interface is 10 MHz max.
*/
void PortWrite_MCP23S17::begin()
{
    pinMode(SS, OUTPUT);                        //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);                     //disable Slave Select
    SPI.begin();
    SPI.beginTransaction(SPISettings (5000000, MSBFIRST, SPI_MODE0)); //control SPI bus, 5 MHz
    //SPI.endTransaction() not called to release SPI bus because keyboard only has one SPI device.

    push(port.num, 0);                          //configure port direction (port.num) to output (0)
}

/* write() sets pin output to logicLevel.
pin is bitwise, where pin being set is 1.
logicLevel is HIGH or LOW.
write() does not overwrite the other pins.
*/
void PortWrite_MCP23S17::write(const uint8_t pin, const bool logicLevel)
{
    if (logicLevel == LOW)
    {
        port.outputVal &= ~pin;                 //set pin output to low
    }
    else
    {
        port.outputVal |= pin;                  //set pin output to high
    }

    push(port.num + 0x12, port.outputVal);      //set GPIO port pin to outputVal
}
