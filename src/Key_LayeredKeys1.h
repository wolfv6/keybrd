#ifndef KEY_LAYEREDKEYS1_H
#define KEY_LAYEREDKEYS1_H
#include <Arduino.h>
#include <inttypes.h>
#include "LayerStateInterface.h"
#include "Key.h"
#include "Key_LayeredKeysBase.h"

/* Most of the Key_LayeredKeys1 functionality is in Key_LayeredKeysBase.
Key_LayeredKeys1 is just like Key_LayeredKeys, but with a distinct refLayerState.
Key_LayeredKeys1 and Key_LayeredKeys can have different size ptrsKeys[].
*/
class Key_LayeredKeys1 : public Key_LayeredKeysBase
{
    private:
        static LayerStateInterface& refLayerState;
    public:
        Key_LayeredKeys1(Key* const ptrsKeys[]) : Key_LayeredKeysBase(ptrsKeys) {}
        virtual uint8_t getActiveLayer();       //get active layer from refLayerState
};
#endif
