#include "Key_LayeredKeysArray.h"

void Key_LayeredKeysArray::press()
{
    layer = refLayerState.getActiveLayer();

    ptrsKeys[layer]->press();
}

void Key_LayeredKeysArray::release()
{
    ptrsKeys[layer]->release();
}
