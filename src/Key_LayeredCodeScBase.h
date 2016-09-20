#ifndef KEY_LAYEREDCODESCBASE_H
#define KEY_LAYEREDCODESCBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code.h"

/* Class Key_LayeredCodeScBase is an abstract base class for 2-layer keys:
    if layerId=0, send code0
    if layerId=1, send scancode1
*/
class Key_LayeredCodeScBase : public Code
{
    private:
        Code& refCode0;
        const uint16_t scancode1;
    protected:
        bool layerId;                           //active layer when key was pressed, 0 or 1
    public:
        Key_LayeredCodeScBase(Code& refCode0, const uint16_t scancode1, uint8_t layerId):
            refCode0(refCode0), scancode1(scancode1), layerId(layerId) { }
        virtual void press()=0;
        virtual void release();
        virtual void pressCode();
};
#endif
