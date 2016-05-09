#include "LED_AVR.h"

void LED_AVR::on()
{
    PORT |= pin;                                //set pin high
}

void LED_AVR::off()
{
    PORT &= ~pin;                               //set pin low
}
