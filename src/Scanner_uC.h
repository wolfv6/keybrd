#ifndef SCANNER_UC_H
#define SCANNER_UC_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <ScannerInterface.h>

/* Scanner_uC class uses Arduino pin numbers (not port pin numbers).
Limit number of readPins to size of read_pins_t, which is defined in config_keybrd.h
*/
class Scanner_uC : public ScannerInterface
{
    private:
        const bool strobeOn;                    //logic level of strobe on, HIGH or LOW
        const bool strobeOff;                   //logic level of strobe off, complement of strobeOn
        const uint8_t* const readPins;          //array of read pin numbers
        const uint8_t readPinCount;             //number of readPins
    public:
        Scanner_uC(const bool strobeOn, const uint8_t readPins[], const uint8_t readPinCount);
        void init(const uint8_t strobePin);
        virtual read_pins_t scan(const uint8_t strobePin);
};
#endif
