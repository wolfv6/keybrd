#ifndef LAYERSTATE_LED_H
#define LAYERSTATE_LED_H

#include <Arduino.h>
#include <inttypes.h>
#include "LayerState.h"
#include "LEDInterface.h"

/* Basic LayerState with layer LED indictor lights.
begin() should be called once to turn on LED for initial active layer.

If LED is on Scanner_IOE, LayerState_LED::begin() should be called after Scanner_IOE::begin()
so that scanner's ports can turn on LayerState_LED's default-layer LED.
*/
class LayerState_LED : public LayerState
{
    private:
        LEDInterface*const *const ptrsLEDs;    //array of LEDs, where layerId is array index
        virtual void setActiveLayer(const uint8_t layerId);//set active layerId and turn on it's LED
    public:
        LayerState_LED(LEDInterface*const ptrsLEDs[]): ptrsLEDs(ptrsLEDs) {}
        void begin();
};
#endif
