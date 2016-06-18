#include "LED_PinNumber.h"

void LED_PinNumber::on()
{
    digitalWrite(pin, HIGH);
}

void LED_PinNumber::off()
{
    digitalWrite(pin, LOW);
}
