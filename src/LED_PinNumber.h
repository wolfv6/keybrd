#ifndef LED_PINNUMBER_H
#define LED_PINNUMBER_H
#include <Arduino.h>
#include <inttypes.h>
#include <LED.h>

/* A LED_PinNumber object is an Aduino pin that is used to power an LED on and off.
*/
class LED_PinNumber: public LED
{
    private:
        const uint8_t pin;

    public:
        LED_PinNumber(const uint8_t pin): pin(pin)
        {
            pinMode(pin, OUTPUT);
        }
        virtual void on();
        virtual void off();
};
#endif
