#ifndef CODE_SC_LED_H
#define CODE_SC_LED_H
#include <Arduino.h>
#include <inttypes.h>
#include <Code.h>
#include <LED.h>

/* Class Code_Sc_LED sends a scancode when press() or release() is called.
"S" stands for Scancode.
*/
class Code_Sc_LED : public Code
{
    private:
        const uint16_t scancode;
        LED& refLED;
    public:
        Code_Sc_LED(const uint16_t scancode, LED& refLED): scancode(scancode), refLED(refLED) { }
        virtual void press();
        virtual void release();
};
#endif
