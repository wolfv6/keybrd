#include "LED_uC.h"

LED_uC::LED_uC(const uint8_t pin) : pin(pin)
{
    pinMode(pin, OUTPUT);
}

void LED_uC::on()
{
    digitalWrite(pin, HIGH);
}

void LED_uC::off()
{
    digitalWrite(pin, LOW);
}
