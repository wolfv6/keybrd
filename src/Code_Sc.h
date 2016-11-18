#ifndef CODE_SC_H
#define CODE_SC_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code.h"

/* Class Code_Sc_LED sends a scancode when press() or release() is called.
"S" stands for Scancode.
*/
class Code_Sc : public Code
{
    private:
        const uint16_t scancode;
    public:
        Code_Sc(const uint16_t scancode): scancode(scancode) { }
        virtual void press();
        virtual void release();
};
#endif
