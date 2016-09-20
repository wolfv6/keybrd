#include "Key_LayeredScScBase.h"

void Key_LayeredScScBase::pressScancode()
{
    if (layerId)
    {
        scancode = scancode1;
    }
    else
    {
        scancode = scancode0;
    }

    Keyboard.press(scancode);
}

void Key_LayeredScScBase::release()
{
    Keyboard.release(scancode);
}
