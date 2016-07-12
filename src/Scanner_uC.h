#ifndef SCANNER_UC_H
#define SCANNER_UC_H
#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <StrobePort.h>
#include <ReadPort.h>

/* Scanner_uC class uses Arduino pin numbers (not port pin numbers).
Constructor is in Scanner_uC.cpp
*/
class Scanner_uC
{
    private:
        static const bool STROBE_ON;            //logic level of strobe on, HIGH or LOW
        static const bool STROBE_OFF;           //logic level of strobe off, complement of STROBE_ON
        const uint8_t STROBE_PIN;               //Arduino pin number connected to this row
        const uint8_t* const READ_PINS;         //array of read pin numbers
        const uint8_t READ_PIN_COUNT;           //number of read pins
    public:
        Scanner_uC(const uint8_t STROBE_PIN,
                const uint8_t READ_PINS[], const uint8_t READ_PIN_COUNT); //todo rename READ_PIN_COUNT to READ_PIN_COUNT ??
        virtual read_pins_t scan(uint8_t& READ_PIN_COUNT);
};
#endif

