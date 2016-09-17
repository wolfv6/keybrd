#ifndef KEY_LAYEREDSCSC_H
#define KEY_LAYEREDSCSC_H
#include <Arduino.h>
#include <inttypes.h>
#include <LayerStateInterface.h>
#include <Key_LayeredScScBase.h>

/* Class Key_LayeredScSc is composed of two scancodes; "S" stands for Scancode.
layer is retreived from refLayerState.
    when layer=0, press sends scancode0
    when layer=1, press sends scancode1
*/
class Key_LayeredScSc : public Key_LayeredScScBase
{
    private:
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredScSc(const uint16_t scancode0, const uint16_t scancode1)
            : Key_LayeredScScBase(scancode0, scancode1) { }
        virtual void press();
};
#endif
