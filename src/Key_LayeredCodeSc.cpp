#include "Key_LayeredCodeSc.h"

void Key_LayeredCodeSc::press()
{
    layerId = refLayerState.getActiveLayer();
    pressCode();
}
