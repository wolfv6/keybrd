#include "LayerState_LED.h"

void LayerState_LED::begin()
{
    ptrsLEDs[getActiveLayer()]->on();
}

void LayerState_LED::setActiveLayer(const uint8_t layer)
{
    ptrsLEDs[activeLayer]->off();
    activeLayer = layer;
    ptrsLEDs[activeLayer]->on();
}
