#include "Key_LayeredKeys.h"

uint8_t Key_LayeredKeys::getActiveLayer()
{
    return refLayerState.getActiveLayer();
}
