#ifndef KEY_LAYEREDKEYS_H
#define KEY_LAYEREDKEYS_H
#include <Arduino.h>
#include <inttypes.h>
#include <LayerStateInterface.h>
#include <Key.h>
#include <Key_LayeredKeysBase.h>

/* Most of the Key_LayeredKeys functionality is in Key_LayeredKeysBase.
*/
class Key_LayeredKeys : public Key_LayeredKeysBase
{
    private:
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredKeys(Key* const ptrsKeys[]) : Key_LayeredKeysBase(ptrsKeys) {}
        virtual uint8_t getActiveLayer();       //get active layer from refLayerState
};
#endif
