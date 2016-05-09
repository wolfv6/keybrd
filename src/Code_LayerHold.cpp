#include "Code_LayerHold.h"

void Code_LayerHold::press()
{
    refStateLayers.hold(layer);
}

void Code_LayerHold::release()
{
    refStateLayers.unhold(layer);
}
