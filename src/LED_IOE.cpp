#include "LED_IOE.h"

void LED_IOE::on()
{
    refPort.write(pin, HIGH);
}

void LED_IOE::off()
{
    refPort.write(pin, LOW);
}
