#include "Code_Sc_LED.h"

void Code_Sc_LED::press()
{
    Keyboard.press(scancode);
    refLED.on();
}

void Code_Sc_LED::release()
{
    Keyboard.release(scancode);
    refLED.off();
}
