#include "PortMCP23S17.h"

/* transfer() writes data to registerAddr, reads portSate from registerAddr, and returns portState.
*/
uint8_t PortMCP23S17::transfer(const uint8_t command, const uint8_t registerAddr, const uint8_t data)
{
    uint8_t portState;                          //bit pattern

    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(command);                    //write or read command
      SPI.transfer(registerAddr);               //register address to write data to
      portState = SPI.transfer(data);           //write data, read portState
    digitalWrite(SS, HIGH);                     //disable Slave Select

    return portState;
}
