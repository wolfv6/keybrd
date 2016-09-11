#include "PortMCP23S17.h"

/* push() writes data to registerAddr.
*/
void PortMCP23S17::push(const uint8_t command, const uint8_t registerAddr, const uint8_t data)
{
    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(command);                    //write command todo also read command?
      SPI.transfer(registerAddr);               //register address to write data to
      SPI.transfer(data);                       //write the data
    digitalWrite(SS, HIGH);                     //disable Slave Select
}
