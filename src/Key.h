//header-guard name needs to be uinique
//arduino\hardware\teensy\avr\cores\teensy\keylayouts.h has #define KEY_H
//Keypad library has a header file Key.h
#ifndef KEY_H_keybrd
#define KEY_H_keybrd

#include <Arduino.h>
#include <inttypes.h>

/* Key is an interface class
*/
class Key
{
    public:
        virtual void press()=0;                 //send scancode to USB for press
        virtual void release()=0;               //send scancode to USB for release
};
#endif
