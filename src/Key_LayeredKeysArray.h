#ifndef KEY_LAYEREDKEYSARRAY_H
#define KEY_LAYEREDKEYSARRAY_H
#include <Arduino.h>
#include <inttypes.h>
#include <LayerStateInterface.h>
#include <Key.h>

/* Class Key_LayeredKeysArray contains an array of Key pointers, one pointer per layer.
Codes are a kind of Key, so the Key pointers can point to Codes as well.

When the key is pressed, active layer is retreived from refLayerState and
the Key object of the active layer is called.
*/
class Key_LayeredKeysArray : public Key
{
    private:
        Key *const *const ptrsKeys;             //array of Key pointers, one Key per layer
        uint8_t layer;                          //active layer when key was pressed
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredKeysArray(Key *const ptrsKeys[]): ptrsKeys(ptrsKeys) {}
        virtual void press();
        virtual void release();
};
#endif
