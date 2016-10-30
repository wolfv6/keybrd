#ifndef LED_SHIFTREG_H
#define LED_SHIFTREG_H
#include <Arduino.h>
#include <inttypes.h>
#include <LEDInterface.h>
#include <PortWriteInterface.h>

/* LED_ShiftReg turns LED on and off.
shift register RCLK pin a.k.a. SS or ST
*/
class LED_ShiftReg: public LEDInterface
{
    private:
        PortWriteInterface& refPort;
        const uint8_t pin;              //bit pattern, 1 is shift-register pin connected to an LED
    public:
        LED_ShiftReg(PortWriteInterface& refPort, uint8_t pin)
            : refPort(refPort), pin(pin) {}
        virtual void on();
        virtual void off();
};
#endif
