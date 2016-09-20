#include "Key_LayeredKeysBase.h"

void Key_LayeredKeysBase::press()
{
    layerId = getActiveLayer();

    ptrsKeys[layerId]->press();
}

void Key_LayeredKeysBase::release()
{
    ptrsKeys[layerId]->release();
}
