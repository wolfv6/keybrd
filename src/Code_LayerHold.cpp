#include "Code_LayerHold.h"

void Code_LayerHold::press()
{
    refLayerState.hold(layer);
}

void Code_LayerHold::release()
{
    refLayerState.unhold(layer);
}
