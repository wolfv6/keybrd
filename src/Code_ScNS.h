#ifndef CODE_SCNS_H
#define CODE_SCNS_H
#include <Arduino.h>
#include <inttypes.h>
#include <Code_AutoShift.h>

/* Class Code_ScNS is composed of one scancode, which it sends when press() or release() is called.
autoShift insures that all MODIFIERKEY_SHIFTs are released.
Letters will still print as capital if CapsLck is on.
"ScNS" stands for Scancode Not Shifted.
If scancode is a letter, CapsLck will invert the case.
Normally this is not a problem because most layer schemes control letter case by shift.
*/
class Code_ScNS: public Code_AutoShift
{
    private:
        const uint16_t scancode;
    public:
        Code_ScNS(const uint16_t scancode): scancode(scancode) { }
        virtual void press();
        virtual void release();
};
#endif
