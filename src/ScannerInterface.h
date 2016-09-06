#ifndef SCANNERINTERFACE_H
#define SCANNERINTERFACE_H

#include <config_keybrd.h>

/* scan() retuns state of readPins.
*/
class ScannerInterface
{
    public:
        virtual void init(const uint8_t strobePin)=0;
        virtual read_pins_t scan(const uint8_t strobePin)=0;
};
#endif
