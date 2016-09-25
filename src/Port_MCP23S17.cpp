#include "Port_MCP23S17.h"

/* transfer() writes data to registerAddr, reads portSate from registerAddr, and returns portState.

MCP23S17 SPI interface is 10 MHz max.
The electrical limitation to bus speed is bus capacitance and the length of the wires involved.
Longer wires require lower clock speeds. 
*/
uint8_t Port_MCP23S17::transfer(const uint8_t command, const uint8_t registerAddr,
        const uint8_t data)
{
    uint8_t portState;                          //bit pattern

    SPI.beginTransaction( SPISettings(5000000, MSBFIRST, SPI_MODE0) ); //control SPI bus, 5 MHz
    digitalWrite(SS, LOW);                      //enable Slave Select
      SPI.transfer(command);                    //write or read command
      SPI.transfer(registerAddr);               //register address to write data to
      portState = SPI.transfer(data);           //write data, read portState
    digitalWrite(SS, HIGH);                     //disable Slave Select
    SPI.endTransaction();

    return portState;
}

/* begin() is called from Scanner_IOE::begin().  Initiates SPI bus.
*/
void Port_MCP23S17::beginProtocol()
{
    pinMode(SS, OUTPUT);                        //configure controller's Slave Select pin to output
    digitalWrite(SS, HIGH);                     //disable Slave Select
    SPI.begin();
}

/* begin() is called from Scanner_IOE::begin().
strobeOn is logic level of strobe on, HIGH or LOW
configure IODIR and GPPU.
*/
void Port_MCP23S17::begin(const uint8_t strobeOn)
{
    uint8_t pullUp;                             //bits, GPPU 0=pull-up disabled, 1=pull-up enabled

    if (strobeOn == LOW)                        //if active low, use internal pull-up resistors
    {
        pullUp = readPins;
    }
    else                                        //active high requires external pull-down resistors
    {
        pullUp = 0;
    }

    transfer(deviceAddr << 1, portNum, readPins); //configure IODIR
    transfer(deviceAddr << 1, portNum + 0x0C, pullUp); //configure GPPU
}

/* write() sets pin output to logicLevel (useful for strobePin, one LED pin, or multiple pins).
pin is bit pattern, where pin being set is 1.
logicLevel is HIGH or LOW.
write() does not overwrite the other pins.
*/
void Port_MCP23S17::write(const uint8_t pin, const bool logicLevel)
{
    if (logicLevel == LOW)
    {
        outputVal &= ~pin;                 //set pin output to low
    }
    else
    {
        outputVal |= pin;                  //set pin output to high
    }

    transfer(deviceAddr << 1, portNum + 0x12, outputVal); //set GPIO port to outputVal
}

/* read() returns portState.  Only portState pins with pull resistors are valid.
*/
uint8_t Port_MCP23S17::read()
{
    return transfer( (deviceAddr << 1) | 1, portNum + 0x12, 0); //read from GPIO
}
