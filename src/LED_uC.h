#ifndef LED_UC_H
#define LED_UC_H
#include <Arduino.h>
#include <inttypes.h>
#include <LEDInterface.h>

/* A LED_uC turns LED on and off.
*/
class LED_uC: public LEDInterface
{
    private:
        const uint8_t pin;                      //Aduino pin that is connected to an LED

    public:
        LED_uC(const uint8_t pin): pin(pin)
        {
            pinMode(pin, OUTPUT);
        }
        virtual void on();
        virtual void off();
};
#endif
