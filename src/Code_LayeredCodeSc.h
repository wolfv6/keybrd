#ifndef CODE_LAYEREDCODESC_H
#define CODE_LAYEREDCODESC_H
#include <Arduino.h>
#include <inttypes.h>
#include <Code_LayeredCodeScBase.h>
#include <StateLayersInterface.h>

/* Class Code_LayeredCodeSc is a 2-layer code, one object for each layer e.g.
    layer0: ms_up    //mouse up
    layer1: KEY_UP   //up arrow
When the key is pressed, the active layer is retrieved from refStateLayers,
 and the object for the active layer is sent to USB.
*/
class Code_LayeredCodeSc : public Code_LayeredCodeScBase
{
    private:
        static StateLayersInterface& refStateLayers;
    public:
        Code_LayeredCodeSc(Code& refCode0, const uint16_t scancode1)
            : Code_LayeredCodeScBase(refCode0, scancode1, 0) { }
        virtual void press();
};
#endif
