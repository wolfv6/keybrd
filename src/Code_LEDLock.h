#ifndef CODE_LEDLOCK_H
#define CODE_LEDLOCK_H
#include <Arduino.h>
#include <inttypes.h>
#include <Code.h>
#include <LED.h>

extern volatile uint8_t keyboard_leds;

/* Class Code_LEDLock turns LED on and off
scancode is KEY_CAPS_LOCK, KEY_SCROLL_LOCK, or KEY_NUM_LOCK

In keybrd sketch, ports should be instantiated before Code_LEDLock is instantiated
because LED.off() needs ports to be configured by port constructor.

If a key does not have an LED indictor light, use Code_S instead e.g.:
    Code_S CapsLck(KEY_CAPS_LOCK);
*/
class Code_LEDLock : public Code
{
    private:
        const uint16_t scancode;
        uint8_t USB_LED_bit;                    //codes used by keyboard output report
        LED& refLED;                            //indicator on keyboard
        void updateLED() const;

    public:
        Code_LEDLock(const uint16_t scancode, LED& refLED);
        virtual void press();
        virtual void release();
};
#endif
