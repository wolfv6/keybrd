#include "Code_LayerLock.h"

void Code_LayerLock::press()
{
    refLayerState.lock(layer);
}

void Code_LayerLock::release()
{
}
