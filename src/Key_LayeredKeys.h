#ifndef KEY_LAYEREDKEYS_H
#define KEY_LAYEREDKEYS_H
#include <Arduino.h>
#include <inttypes.h>
#include <LayerStateInterface.h>
#include <Key.h>

/* Class Key_LayeredKeys contains an array of Key pointers, one pointer per layer.
Codes are a kind of Key, so the Key pointers can point to Codes or Keys.

When the key is pressed, active layerId is retreived from refLayerState and
the Key object of the active layerId is called.
*/
class Key_LayeredKeys : public Key
{
    private:
        Key*const *const ptrsKeys;             //array of Key pointers, one Key per layer
        uint8_t layerId;                          //active layer when key was pressed
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredKeys(Key* const ptrsKeys[]): ptrsKeys(ptrsKeys) {}
        virtual void press();
        virtual void release();
};
#endif
