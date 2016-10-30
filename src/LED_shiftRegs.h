#ifndef LED_SHIFTREGS_H
#define LED_SHIFTREGS_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <LEDInterface.h>

/* A LED_shiftRegs turns LED on and off.
shift register RCLK pin a.k.a. SS or ST
*/
class LED_shiftRegs: public LEDInterface
{
    private:
        const uint8_t slaveSelect;//controller pin number connected to shift register RCLK
        const uint8_t pin;        //bit pattern, shift register pin that is connected to an LED
    public:
        LED_shiftRegs(const uint8_t slaveSelect, const uint8_t pin);
        void begin();
        virtual void on();
        virtual void off();
};
#endif
