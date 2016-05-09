#include "Code_LayerLock.h"

void Code_LayerLock::press()
{
    refStateLayers.lock(layer);
}

void Code_LayerLock::release()
{
}
