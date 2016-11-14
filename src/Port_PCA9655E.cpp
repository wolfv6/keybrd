#include "Port_PCA9655E.h"

/* beginProtocol() is called from Scanner_IOE::begin().  Initiates I2C bus.

PCA9655E supports I2C SCL Clock Frequencies: 100 kHz, 400 kHz, 1000 kHz (Datasheet page 1 & 6)
The electrical limitation to bus speed is bus capacitance and the length of the wires involved.
Longer wires require lower clock speeds.
 http://playground.arduino.cc/Main/WireLibraryDetailedReference > Wire.setclock()
*/
void Port_PCA9655E::beginProtocol()
{
    Wire.begin();                               //initiate I2C bus to 100 kHz
    //Wire.setClock(400000L);                     //set I2C bus to 400 kHz (have not tested 400 kHz)
}

/* begin() is called from Scanner_IOE::begin().
Configures read pins to input.
strobeOn is not used because PCA9655E has no internal pull-up resistors.
*/
void Port_PCA9655E::begin(const uint8_t strobeOn)
{
    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 6);                    //configure direction
    Wire.write(readPins);                       //0=output (for strobe and LED), 1=input (for read)
    Wire.endTransmission();
}

/* setLow() sets pin output LOW.
pin is bit pattern, where pin being set is 1.
*/
void Port_PCA9655E::setLow(const uint8_t pin)
{
    outputVal &= ~pin;                          //set pin output to low

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 2);                    //output Byte command
    Wire.write(outputVal);
    Wire.endTransmission();
}

/* setHigh() sets pin output HIGH.
pin is bit pattern, where pin being set is 1.
*/
void Port_PCA9655E::setHigh(const uint8_t pin)
{
    outputVal |= pin;                           //set pin output to high

    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum + 2);                    //output Byte command
    Wire.write(outputVal);
    Wire.endTransmission();
}

/* read() returns portState.
Only portState bits of readPins are valid.
*/
uint8_t Port_PCA9655E::read()
{
    Wire.beginTransmission(deviceAddr);
    Wire.write(portNum);                        //input byte command
    Wire.endTransmission(false);                //PCA9655E needs false to send a restart

    Wire.requestFrom(deviceAddr, 1u);           //request one byte from input port

    return Wire.read();
}
