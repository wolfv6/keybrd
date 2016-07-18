#ifndef SCANNER_UC_H
#define SCANNER_UC_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <PortWrite.h>
#include <PortRead.h>

/* Scanner_uC class uses Arduino pin numbers (not port pin numbers).
Constructor is in Scanner_uC.cpp
*/
class Scanner_uC
{
    private:
        static const bool STROBE_ON;            //logic level of strobe on, HIGH or LOW
        static const bool STROBE_OFF;           //logic level of strobe off, complement of STROBE_ON
        const uint8_t strobePin;                //Arduino pin number connected to this row
        const uint8_t* const readPins;          //array of read pin numbers
        const uint8_t readPinCount;             //number of read pins
    public:
        Scanner_uC(const uint8_t strobePin,
                   const uint8_t readPins[], const uint8_t readPinCount);
        virtual read_pins_t scan();
};
#endif

