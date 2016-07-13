#ifndef LED_UC_H
#define LED_UC_H
#include <Arduino.h>
#include <inttypes.h>
#include <LED.h>

/* A LED_uC object is an Aduino pin that is used to power an LED on and off.
*/
class LED_uC: public LED
{
    private:
        const uint8_t pin;

    public:
        LED_uC(const uint8_t pin): pin(pin)
        {
            pinMode(pin, OUTPUT);
        }
        virtual void on();
        virtual void off();
};
#endif
