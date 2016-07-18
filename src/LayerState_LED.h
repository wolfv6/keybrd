#ifndef LAYERSTATE_LED_H
#define LAYERSTATE_LED_H

#include <Arduino.h>
#include <inttypes.h>
#include <LayerState.h>
#include <LED.h>

/* Basic LayerState with layer LED indictor lights.
begin() should be called once to turn on LED for initial active layer.
*/
class LayerState_LED : public LayerState
{
    private:
        LED*const *const ptrsLEDs;              //array of LEDs, where layer id is array index
        virtual void setActiveLayer(const uint8_t layer); //set active layer and turn on it's LED
    public:
        LayerState_LED(LED*const ptrsLEDs[]): ptrsLEDs(ptrsLEDs) {}
        void begin();
};
#endif
