#include "LayerState.h"

void LayerState::hold(const uint8_t layer)
{
    setActiveLayer(layer);
}

void LayerState::unhold(const uint8_t layer)
{
    if (layer == activeLayer);
    {
        setActiveLayer(lockedLayer);
    }
}

void LayerState::lock(const uint8_t layer)
{
    setActiveLayer(layer);
    lockedLayer = layer;
}

/*Derived classes override setActiveLayer() to also set LED indicator lights e.g. LayerState_LED
*/
void LayerState::setActiveLayer(const uint8_t layer)
{
    activeLayer = layer;
}

uint8_t LayerState::getActiveLayer()
{
    return activeLayer;
}
