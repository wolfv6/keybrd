#include "Code_LayeredScSc.h"

void Code_LayeredScSc::press()
{
    layer = refLayerState.getActiveLayer();
    pressScancode();
}
