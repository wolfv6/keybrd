#ifndef KEY_LAYEREDKEYSBASE_H
#define KEY_LAYEREDKEYSBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include <LayerStateInterface.h>
#include <Key.h>

/* Class Key_LayeredKeysBase contains an array of Key pointers, one pointer per layer.
Codes are a kind of Key, so the Key pointers can point to Codes or Keys.

When the key is pressed, active layerId is retreived and the Key object of that layer is called.

Design note:
Child classes (Key_LayeredKeys and Key_LayeredKeys1) have distinct static refLayerState
and different size ptrsKeys[].
That way Key_LayeredKeys instantiations don't need a LayerState argument,
which is significant for a sketch with 100 keys.
*/
class Key_LayeredKeysBase : public Key
{
    private:
        Key*const *const ptrsKeys;              //array of Key pointers, one Key per layer
        uint8_t layerId;                        //active layer when key was pressed
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredKeysBase(Key* const ptrsKeys[]): ptrsKeys(ptrsKeys) {}
        virtual uint8_t getActiveLayer()=0;
        virtual void press();
        virtual void release();
};
#endif
