#include "LED_Port.h"

void LED_Port::on()
{
    refPort.writeHigh(pin);
}

void LED_Port::off()
{
    refPort.writeLow(pin);
}
