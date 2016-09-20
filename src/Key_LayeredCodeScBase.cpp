#include "Key_LayeredCodeScBase.h"

void Key_LayeredCodeScBase::pressCode()
{
    if (layerId)
    {
        Keyboard.press(scancode1);
    }
    else
    {
        refCode0.press();
    }
}

void Key_LayeredCodeScBase::release()
{
    if (layerId)
    {
        Keyboard.release(scancode1);
    }
    else
    {
        refCode0.release();
    }
}
