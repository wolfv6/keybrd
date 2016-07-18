#ifndef PORTREAD_H
#define PORTREAD_H
#include <Arduino.h>
#include <inttypes.h>

/*
PortRead is an abstract base class.
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.

If your 8-bit AVR (Teensy 2) is running low on memory, using a smaller read_pins_t type saves SRAM.
Details are in config_key.h
*/
class PortRead
{
    protected:
        const uint8_t readPins;                  //bitwise pin configuration, 1 means read column
    public:
        PortRead(const uint8_t readPins): readPins(readPins) {}
        virtual uint8_t read()=0;
};
#endif
