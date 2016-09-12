#include "PortWrite_PCA9655E.h"

/* begin() is called from Scanner_IOE::begin().
Initiates I2C bus and configures port pins to output.
PCA9655E supports I2C SCL Clock Frequencies: 100 kHz, 400 kHz, 1000 kHz (Datasheet page 1 & 6)
The electrical limitation to bus speed is bus capacitance and the length of the wires involved.
Longer wires require lower clock speeds. 
 http://playground.arduino.cc/Main/WireLibraryDetailedReference > Wire.setclock()
*/
void PortWrite_PCA9655E::begin()
{
    Wire.begin();                               //initiate I2C bus to 100 kHz
    //Wire.setClock(400000L);                     //set I2C bus to 400 kHz (have not tested 400 kHz)

    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 6);                   //configuration byte command
    Wire.write(0);                              //configure all pins as output
    Wire.endTransmission();
}

/* write() sets pin output to logicLevel.
pin is bitwise, where pin being strobed is 1.
logicLevel is HIGH or LOW.
write() does not overwrite the other pins.
*/
void PortWrite_PCA9655E::write(const uint8_t pin, const bool logicLevel)
{
    if (logicLevel == LOW)                      //if pin low
    {
        port.outputVal &= ~pin;                 //set pin output to low
    }
    else                                        //if strobestrobe high
    {
        port.outputVal |= pin;                  //set pin output to high
    }

    Wire.beginTransmission(port.DEVICE_ADDR);
    Wire.write(port.num + 2);                   //output Byte command
    Wire.write(port.outputVal);
    Wire.endTransmission();
}
