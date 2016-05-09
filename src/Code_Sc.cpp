#include "Code_Sc.h"

void Code_Sc::press()
{
    Keyboard.press(scancode);
}

void Code_Sc::release()
{
    Keyboard.release(scancode);
}
