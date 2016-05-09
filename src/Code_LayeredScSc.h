#ifndef CODE_LAYEREDSCSC_H
#define CODE_LAYEREDSCSC_H
#include <Arduino.h>
#include <inttypes.h>
#include <StateLayersInterface.h>
#include <Code_LayeredScScBase.h>

/* Class Code_LayeredScSc is composed of two scancodes; "S" stands for Scancode.
layer is retreived from refStateLayers.
    when layer=0, press sends scancode0
    when layer=1, press sends scancode1
*/
class Code_LayeredScSc : public Code_LayeredScScBase
{
    private:
        static StateLayersInterface& refStateLayers;
    public:
        Code_LayeredScSc(const uint16_t scancode0, const uint16_t scancode1)
            : Code_LayeredScScBase(scancode0, scancode1) { }
        virtual void press();
};
#endif
