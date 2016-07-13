#include "LED_uC.h"

void LED_uC::on()
{
    digitalWrite(pin, HIGH);
}

void LED_uC::off()
{
    digitalWrite(pin, LOW);
}
