#ifndef CODE_AUTOSHIFT_H
#define CODE_AUTOSHIFT_H
#include "Code.h"
#include "Code_Shift.h"

/* Code_AutoShift is an abstract base class for Codes that depend on automatic shifting.
Code_AutoShift can manage one or more shift keys.

Example initialization:
    const Code_Shift s_shift(MODIFIERKEY_LEFT_SHIFT);
    const Code_Shift *const ptrsS[] = { &s_shift };
    const Code_Shift *const *const Code_AutoShift::ptrsShifts = ptrsS;
    const uint8_t Code_AutoShift::shiftCount = sizeof(ptrsShifts)/sizeof(*ptrsShifts);
The two Code_Shift pointer arrays (ptrsShifts and ptrsS) must have distinct names.

Automatic shifting is usful on multi-layered keyboards.
The shift state for Code_ScS and Code_ScNS are changed and restored:
    Code_ScS object is a scancode shifted          e.g. '%' in symbols layer
    Code_ScNS object is a scancode not shifted     e.g. '5' in numbers layer

keyboards without Code_ScS and Code_ScNS can omit ptrsShifts[] array and 
and place scancode MODIFIERKEY_LEFT_SHIFT directly in Code_Sc:
    Code_Sc s_shift(MODIFIERKEY_LEFT_SHIFT);
*/
class Code_AutoShift : public Code
{
    private:
        static Code_Shift *const *const ptrsShifts; //array of Code_Shift pointers
        static const uint8_t shiftCount;
    protected:
        bool isShifted() const;
        void releaseAllShifts() const;
        void restoreAllShifts() const;
    public:
        virtual void press()=0;
        virtual void release()=0;
};
#endif
