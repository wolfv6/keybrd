#include "LED_Port.h"

void LED_Port::on()
{
    refPort.setHigh(pin);
}

void LED_Port::off()
{
    refPort.setLow(pin);
}
