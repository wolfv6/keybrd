#include "Key_LayeredKeysArray.h"

void Key_LayeredKeysArray::press()
{
    layer = refStateLayers.getActiveLayer();

    ptrsKeys[layer]->press();
}

void Key_LayeredKeysArray::release()
{
    ptrsKeys[layer]->release();
}
