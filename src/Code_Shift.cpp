#include "Code_Shift.h"

void Code_Shift::press()
{
    Keyboard.press(scancode);
    pressed = true;
}

void Code_Shift::release()
{
    Keyboard.release(scancode);
    pressed = false;
}

bool Code_Shift::isPressed()
{
    return pressed;
}

void Code_Shift::unpress()
{
    if (pressed)
    {
        Keyboard.release(scancode);
    }
}

void Code_Shift::restorePressed()
{
    if (pressed)
    {
        Keyboard.press(scancode);
    }
}
