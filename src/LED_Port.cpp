#include "LED_Port.h"

void LED_Port::on()
{
    refPort.write(pin, HIGH);
}

void LED_Port::off()
{
    refPort.write(pin, LOW);
}
