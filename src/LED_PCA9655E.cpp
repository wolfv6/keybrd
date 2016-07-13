#include "LED_PCA9655E.h"

void LED_PCA9655E::on()
{
    refPort.write(pin, HIGH);
}

void LED_PCA9655E::off()
{
    refPort.write(pin, LOW);
}
