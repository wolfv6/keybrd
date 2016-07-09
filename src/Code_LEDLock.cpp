#include "Code_LEDLock.h"

/* USB_LED_bit are codes from http://www.usb.org/developers/hidpage/HID1_11.pdf keyboard output report
*/
Code_LEDLock::Code_LEDLock(const uint16_t scancode, LED& refLED)
    : scancode(scancode), refLED(refLED)
{
    switch (scancode)                           //initilize USB_LED_bit for given scancode
    {
    case KEY_NUM_LOCK:
        USB_LED_bit = 1<<0;
        break;
    case KEY_CAPS_LOCK:
        USB_LED_bit = 1<<1;
        break;
    case KEY_SCROLL_LOCK:
        USB_LED_bit = 1<<2;
        break;
    /* guessing at these case names:
    case KEY_COMPOSE:                           //for separate accent keys
        USB_LED_bit = 1<<3; break;
        break;
    case KEY_KANA:                              //for Japanese keyboards
        USB_LED_bit = 1<<4; break;
        break;
    */
    }
}

void Code_LEDLock::press()
{
    Keyboard.press(scancode);
    updateLED();
}

void Code_LEDLock::release()
{
    Keyboard.release(scancode);
}

/* This comment is for Arduino board, because Arduino boards may need a different implementation.
updateLED() has NOT been tested on an Arduino board.
updateLED() has been tested on teensy 2.0 (not an Arduino board).
The variable "keyboard_leds" is in /opt/arduino-1.6.7/hardware/teensy/avr/cores/usb_hid/usb.c
 // 1=num lock, 2=caps lock, 4=scroll lock, 8=compose, 16=kana
 https://forum.pjrc.com/threads/25368-How-do-I-receive-a-numlock-capslock-LED-signal-from-the-PC
The word "keyboard_leds does not appear in "Arduino\hardware\arduino\cores\
This shows how to hack KeyReport in Arduino: https://www.sparkfun.com/tutorials/337
TMK firmware, which is not Arduino, uses variable "usb_led" instead of "keyboard_leds"
 http://deskthority.net/workshop-f7/how-to-build-your-very-own-keyboard-firmware-t7177.html >usb_led
*/
void Code_LEDLock::updateLED() const
{
/* KEY_SCROLL_LOCK is not working on Linux with Teensy2.0.
This debug code prints "keyboard_leds=0" when scrollLock is pressed:
    Keyboard.print(F(" keyboard_leds="));
    Keyboard.print(keyboard_leds); //KEY_NUM_LOCK:1, KEY_CAPS_LOCK:2, KEY_SCROLL_LOCK:0
    Keyboard.print(" ");
*/
    if (keyboard_leds & USB_LED_bit)            //if USB_LED_bit is set
    {
        refLED.off();       //LED on-off seem inverted, but it works for active low and active high
    }
    else
    {
        refLED.on();
    }
}
