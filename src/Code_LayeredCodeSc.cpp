#include "Key_LayeredCodeSc.h"

void Key_LayeredCodeSc::press()
{
    layer = refLayerState.getActiveLayer();
    pressCode();
}
