#include "Key_LayeredScSc.h"

void Key_LayeredScSc::press()
{
    layer = refLayerState.getActiveLayer();
    pressScancode();
}
