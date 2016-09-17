#ifndef KEY_LAYEREDCODESC_H
#define KEY_LAYEREDCODESC_H
#include <Arduino.h>
#include <inttypes.h>
#include <Key_LayeredCodeScBase.h>
#include <LayerStateInterface.h>

/* Class Key_LayeredCodeSc is a 2-layer code, one object for each layer e.g.
    layer0: ms_up    //mouse up
    layer1: KEY_UP   //up arrow
When the key is pressed, the active layer is retrieved from refLayerState,
 and the object for the active layer is sent to USB.
*/
class Key_LayeredCodeSc : public Key_LayeredCodeScBase
{
    private:
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredCodeSc(Code& refCode0, const uint16_t scancode1)
            : Key_LayeredCodeScBase(refCode0, scancode1, 0) { }
        virtual void press();
};
#endif
