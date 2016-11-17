#include "Code_LayerHoldShift.h"

void Code_LayerHoldShift::press()
{
    refLayerState.hold(layerId);
    refCodeShift.press();
}

void Code_LayerHoldShift::release()
{
    refLayerState.unhold(layerId);
    refCodeShift.release();
}
