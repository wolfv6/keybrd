#include "PortWrite_PCA9655E.h"

/* begin() is called from Scanner_IOE::begin().
Configures write pins to output.
*/
void PortWrite_PCA9655E::begin()
{
    Wire.begin();

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
