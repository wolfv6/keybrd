#ifndef KEY_LAYEREDCODESCBASE_H
#define KEY_LAYEREDCODESCBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include "Code.h"

/* Class Key_LayeredCodeScBase is a 2-layer code, with one object for each layer e.g.
    layer0: ms_up    //mouse up
    layer1: KEY_UP   //up arrow
When the key is pressed, the active layer is retrieved from refLayerState,
 and the object for the active layer is sent to USB.
*/
class Key_LayeredCodeScBase : public Code
{
    private:
        Code& refCode0;
        const uint16_t scancode1;
    protected:
        bool layer;
    public:
        Key_LayeredCodeScBase(Code& refCode0, const uint16_t scancode1, uint8_t layer):
            refCode0(refCode0), scancode1(scancode1), layer(layer) { }
        virtual void press()=0;
        virtual void release();
        virtual void pressCode();
};
#endif
