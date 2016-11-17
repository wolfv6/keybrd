#include "Port_MCP23017.h"

/* beginProtocol() is called from Scanner_IOE::begin().  Initiates I2C bus.

MCP23017 supports I2C SCL Clock Frequencies: 100 kHz, 400 kHz, 1000 kHz (Datasheet page 1 & 6)
The electrical limitation to bus speed is bus capacitance and the length of the wires involved.
Longer wires require lower clock speeds.
 http://playground.arduino.cc/Main/WireLibraryDetailedReference > Wire.setclock()
*/
void Port_MCP23017::beginProtocol()
{
    Wire.begin();                               //initiate I2C bus to 100 kHz
}

/* begin() is called from Scanner_IOE::begin().
Configures port's IODIR and GPPU.
*/
void Port_MCP23017::begin(const uint8_t activeState)
{
    uint8_t pullUp;                             //bits, GPPU 0=pull-up disabled, 1=pull-up enabled

    if (activeState == LOW)                     //if active low
    {
        pullUp = readPins;              //0=pull-up disabled (for LED), 1=pull-up enabled (for read)
    }
    else                                        //if active high
    {
        pullUp = 0;                             //0=pull-up disabled (external pull-down resistors)
    }

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum);                        //IODIR
    Wire.write(readPins);                       //0=output (for strobe and LED), 1=input (for read)
    Wire.endTransmission();

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 0x0C);                 //GPPU
    Wire.write(pullUp);
    Wire.endTransmission();
}

/* writeLow() sets pin output LOW.
pin is bit pattern, where pin being set is 1.
*/
void Port_MCP23017::writeLow(const uint8_t pin)
{
    outputVal &= ~pin;                          //set pin output to low

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 0x12);                 //GPIO
    Wire.write(outputVal);
    Wire.endTransmission();
}

/* writeHigh() sets pin output HIGH.
pin is bit pattern, where pin being set is 1.
*/
void Port_MCP23017::writeHigh(const uint8_t pin)
{
    outputVal |= pin;                  //set pin output to high

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 0x12);                 //GPIO
    Wire.write(outputVal);
    Wire.endTransmission();
}

/* read() returns portState.
Only portState bits of readPins are valid.
*/
uint8_t Port_MCP23017::read()
{
    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 0x12);                 //GPIO
    Wire.endTransmission(false);                //MCP23017 needs false to send a restart

    Wire.requestFrom(deviceAddr, 1u);           //request one byte from input port

    return Wire.read();
}
