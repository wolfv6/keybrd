#ifndef KEY_LAYERED2SCANCODES_H
#define KEY_LAYERED2SCANCODES_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code.h"

/* Class Key_LayeredScScBase is an abstract base class for 2-layer keys:
    if layerId=0, send scancode0
    if layerId=1, send scancode1
*/
class Key_LayeredScScBase : public Code
{
    private:
        const uint16_t scancode0;
        const uint16_t scancode1;
        uint16_t scancode;
    protected:
        bool layerId;                           //active layer when key was pressed, 0 or 1
    public:
        Key_LayeredScScBase(const uint16_t scancode0, const uint16_t scancode1):
            scancode0(scancode0), scancode1(scancode1), layerId(0) { }
        virtual void press()=0;
        virtual void release();
        void pressScancode();
};
#endif
