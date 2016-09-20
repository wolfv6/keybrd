#include "Code_LayerHold.h"

void Code_LayerHold::press()
{
    refLayerState.hold(layerId);
}

void Code_LayerHold::release()
{
    refLayerState.unhold(layerId);
}
