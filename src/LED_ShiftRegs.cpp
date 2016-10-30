#include "LED_ShiftRegs.h"

/* constructor
*/
LED_ShiftRegs::LED_ShiftRegs(const uint8_t slaveSelect, const uint8_t pin)
    :slaveSelect(slaveSelect), pin(pin)
{
    pinMode(slaveSelect, OUTPUT);
}

/* begin() should be called once from sketch setup().
Initializes shift register's shift/load pin.
*/
void LED_ShiftRegs::begin()
{
    SPI.begin();
    digitalWrite(slaveSelect, HIGH);
}

//todo preserve other LED values, similar to Port_PCA9655E outputVal
void LED_ShiftRegs::on()
{
    digitalWrite(slaveSelect, LOW);
    SPI.transfer(pin);
    digitalWrite (slaveSelect, HIGH);
}

void LED_ShiftRegs::off()
{
    digitalWrite(slaveSelect, LOW);
    SPI.transfer(0);
    digitalWrite (slaveSelect, HIGH);
}
