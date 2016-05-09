#include "Code_LayeredCodeSc.h"

void Code_LayeredCodeSc::press()
{
    layer = refStateLayers.getActiveLayer();
    pressCode();
}
