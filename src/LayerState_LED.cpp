#include "LayerState_LED.h"

void LayerState_LED::begin()
{
    ptrsLEDs[getActiveLayer()]->on();
}

void LayerState_LED::setActiveLayer(const uint8_t layerId)
{
    ptrsLEDs[activeLayer]->off();
    activeLayer = layerId;
    ptrsLEDs[activeLayer]->on();
}
