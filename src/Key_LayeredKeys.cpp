#include "Key_LayeredKeys.h"

void Key_LayeredKeys::press()
{
    layer = refLayerState.getActiveLayer();

    ptrsKeys[layer]->press();
}

void Key_LayeredKeys::release()
{
    ptrsKeys[layer]->release();
}
