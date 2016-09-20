#include "Key_LayeredKeys.h"

void Key_LayeredKeys::press()
{
    layerId = refLayerState.getActiveLayer();

    ptrsKeys[layerId]->press();
}

void Key_LayeredKeys::release()
{
    ptrsKeys[layerId]->release();
}
