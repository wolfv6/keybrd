#include "Code_ScNS.h"

void Code_ScNS::press()
{
    releaseAllShifts();
    Keyboard.press(scancode);
    restoreAllShifts();
}

void Code_ScNS::release()
{
    Keyboard.release(scancode);
}
