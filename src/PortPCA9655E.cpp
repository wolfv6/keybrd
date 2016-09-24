#include "PortPCA9655E.h"

/* begin() is called from Scanner_IOE::begin().  Initiates I2C bus.

PCA9655E supports I2C SCL Clock Frequencies: 100 kHz, 400 kHz, 1000 kHz (Datasheet page 1 & 6)
The electrical limitation to bus speed is bus capacitance and the length of the wires involved.
Longer wires require lower clock speeds. 
 http://playground.arduino.cc/Main/WireLibraryDetailedReference > Wire.setclock()
*/
void PortPCA9655E::beginProtocol()
{
    Wire.begin();                               //initiate I2C bus to 100 kHz
    //Wire.setClock(400000L);                     //set I2C bus to 400 kHz (have not tested 400 kHz)
}

/* begin() is called from Scanner_IOE::begin().
Configures read pins to input.
strobeOn is not used because PCA9655E has no pull-up resistors.
*/
void PortPCA9655E::begin(const uint8_t strobeOn)
{
    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 6);                    //configuration byte command
    Wire.write(readPins);                       //0=output (for strobe and LED), 1=input (for read)
    Wire.endTransmission();
}

/* write() sets pin output to logicLevel.
pin is bit pattern, where pin being strobed is 1.
logicLevel is HIGH or LOW.
write() does not overwrite the other pins.
*/
void PortPCA9655E::write(const uint8_t pin, const bool logicLevel)
{
    if (logicLevel == LOW)
    {
        outputVal &= ~pin;                      //set pin output to low
    }
    else
    {
        outputVal |= pin;                       //set pin output to high
    }

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 2);                    //output Byte command
    Wire.write(outputVal);
    Wire.endTransmission();
}

/* read() returns portState.
Only portState bits of readPins are valid.
*/
uint8_t PortPCA9655E::read()
{
    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum);                        //input byte command
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(deviceAddr, 1u);           //request one byte from input port

    return Wire.read();
}
