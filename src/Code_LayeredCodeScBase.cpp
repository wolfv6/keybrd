#include "Code_LayeredCodeScBase.h"

void Code_LayeredCodeScBase::pressCode()
{
    if (layer)
    {
        Keyboard.press(scancode1);
    }
    else
    {
        refCode0.press();
    }
}

void Code_LayeredCodeScBase::release()
{
    if (layer)
    {
        Keyboard.release(scancode1);
    }
    else
    {
        refCode0.release();
    }
}
