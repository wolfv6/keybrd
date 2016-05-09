#include "Code_LayeredScScBase.h"

void Code_LayeredScScBase::pressScancode()
{
    if (layer)
    {
        scancode = scancode1;
    }
    else
    {
        scancode = scancode0;
    }

    Keyboard.press(scancode);
}

void Code_LayeredScScBase::release()
{
    Keyboard.release(scancode);
}
