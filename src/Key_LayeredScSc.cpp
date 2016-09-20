#include "Key_LayeredScSc.h"

void Key_LayeredScSc::press()
{
    layerId = refLayerState.getActiveLayer();
    pressScancode();
}
