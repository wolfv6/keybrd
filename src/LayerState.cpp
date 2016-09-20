#include "LayerState.h"

void LayerState::hold(const uint8_t layerId)
{
    setActiveLayer(layerId);
}

void LayerState::unhold(const uint8_t layerId)
{
    if (layerId == activeLayer);
    {
        setActiveLayer(lockedLayer);
    }
}

void LayerState::lock(const uint8_t layerId)
{
    setActiveLayer(layerId);
    lockedLayer = layerId;
}

/*Derived classes override setActiveLayer() to also set LED indicator lights e.g. LayerState_LED
*/
void LayerState::setActiveLayer(const uint8_t layerId)
{
    activeLayer = layerId;
}

uint8_t LayerState::getActiveLayer()
{
    return activeLayer;
}
