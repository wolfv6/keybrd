#ifndef KEY_LAYERED2SCANCODES_H
#define KEY_LAYERED2SCANCODES_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code.h"

/* Class Key_LayeredScScBase is an abstract base class.  It is composed of two scancodes:
    if layer=0, send scancode0
    if layer=1, send scancode1
*/
class Key_LayeredScScBase : public Code
{
    private:
        const uint16_t scancode0;
        const uint16_t scancode1;
        uint16_t scancode;
    protected:
        bool layer;                          //0 or 1
    public:
        Key_LayeredScScBase(const uint16_t scancode0, const uint16_t scancode1):
            scancode0(scancode0), scancode1(scancode1), layer(0) { }
        virtual void press()=0;
        virtual void release();
        void pressScancode();
};
#endif
