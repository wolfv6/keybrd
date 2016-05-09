#ifndef CODE_SHIFT_H
#define CODE_SHIFT_H
#include <Arduino.h>
#include <inttypes.h>
#include <Code.h>

/* Class Code_Shift sends shift scancode for multi-layered keybrds.
Explanation in Code_AutoShift.h
*/
class Code_Shift : public Code
{
    private:
        bool pressed;                           //state of physical shift key, false means released
        const uint16_t scancode;                //MODIFIERKEY_LEFT_SHIFT or MODIFIERKEY_RIGHT_SHIFT
    public:
        Code_Shift(const uint16_t scancode) : pressed(false), scancode(scancode) {}
        virtual void press();
        virtual void release();
        bool isPressed();
        void unpress();
        void restorePressed();
};
#endif
