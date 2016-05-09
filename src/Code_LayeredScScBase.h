#ifndef CODE_LAYERED2SCANCODES_H
#define CODE_LAYERED2SCANCODES_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code.h"

/* Class Code_LayeredScScBase is an abstract base class.  It is composed of two scancodes:
    if layer=0, send scancode0
    if layer=1, send scancode1
*/
class Code_LayeredScScBase : public Code
{
    private:
        const uint16_t scancode0;
        const uint16_t scancode1;
        uint16_t scancode;
    protected:
        bool layer;                          //0 or 1
    public:
        Code_LayeredScScBase(const uint16_t scancode0, const uint16_t scancode1):
            scancode0(scancode0), scancode1(scancode1), layer(0) { }
        virtual void press()=0;
        virtual void release();
        void pressScancode();
};
#endif
