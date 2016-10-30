#include "LED_ShiftReg.h"

void LED_ShiftReg::on()
{
    refPort.write(pin, HIGH);
}

void LED_ShiftReg::off()
{
    refPort.write(pin, LOW);
}
