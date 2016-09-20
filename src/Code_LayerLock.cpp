#include "Code_LayerLock.h"

void Code_LayerLock::press()
{
    refLayerState.lock(layerId);
}

void Code_LayerLock::release()
{
}
