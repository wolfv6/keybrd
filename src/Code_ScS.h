#ifndef CODE_ScS_H
#define CODE_ScS_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code_AutoShift.h"

/* Class Code_ScS contains one scancode, which it sends when press() or release() is called.
autoShift insures that MODIFIERKEY_LEFT_SHIFT is pressed.
"SS" stands for Scancode Shifted.
If scancode is a letter, CapsLck will invert the case.
Normally this is not a problem because most layer schemes control letter case by shift.
*/
class Code_ScS: public Code_AutoShift
{
    private:
        const uint16_t scancode;
    public:
        Code_ScS(const uint16_t scancode): scancode(scancode) { }
        virtual void press();
        virtual void release();
};
#endif
