#ifndef LED_AVR_H
#define LED_AVR_H
#include <Arduino.h>
#include <inttypes.h>
#include <LED.h>

/* A LED_AVR object is an AVR pin that is used to power an LED on and off.
DDRx Data Direction Register is configured as output in RowPort_AVR constructor.
*/
class LED_AVR: public LED
{
    private:
        volatile unsigned char& PORT;
        const uint8_t pin;                      //bitwise pin to LED

    public:
        LED_AVR(volatile unsigned char& PORTx, const uint8_t pin): PORT(PORTx), pin(pin) {}
        virtual void on();
        virtual void off();
};
#endif
