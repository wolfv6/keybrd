#include "Code_ScS.h"

void Code_ScS::press()
{
    if (isShifted())
    {
        Keyboard.press(scancode);
    }
    else
    {
        Keyboard.press(MODIFIERKEY_LEFT_SHIFT); //temporarily shift
        Keyboard.press(scancode);
        Keyboard.release(MODIFIERKEY_LEFT_SHIFT); //restore
    }
}

void Code_ScS::release()
{
    Keyboard.release(scancode);
}
