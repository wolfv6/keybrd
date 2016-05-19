#include "StateLayers.h"

void StateLayers::hold(const uint8_t layer)
{
    setActiveLayer(layer);
}

void StateLayers::unhold(const uint8_t layer)
{
    if (layer == activeLayer);
    {
        setActiveLayer(lockedLayer);
    }
}

void StateLayers::lock(const uint8_t layer)
{
    setActiveLayer(layer);
    lockedLayer = layer;
}

//Derived classes override setActiveLayer() to also set LED indicator lights.
void StateLayers::setActiveLayer(const uint8_t layer)
{
    activeLayer = layer;
}

uint8_t StateLayers::getActiveLayer()
{
    return activeLayer;
}
