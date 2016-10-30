#include "Port_ShiftRegs.h"

Port_ShiftRegs::Port_ShiftRegs(const uint8_t slaveSelect) : slaveSelect(slaveSelect)
{
    pinMode(slaveSelect, OUTPUT);
}

/* begin() should be called once from sketch setup().
Initializes shift register's shift/load pin.
*/
void Port_ShiftRegs::begin()
{
    digitalWrite(slaveSelect, HIGH);
    SPI.begin();
}

void Port_ShiftRegs::write(const uint8_t pin, const bool logicLevel)
{
    if (logicLevel == LOW)
    {
        outputVal &= ~pin;                      //set pin output to low
    }
    else
    {
        outputVal |= pin;                       //set pin output to high
    }

    digitalWrite(slaveSelect, LOW);
    SPI.transfer(outputVal);
    digitalWrite (slaveSelect, HIGH);
}
