#ifndef PORTWRITEINTERFACE_H
#define PORTWRITEINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>

/*
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.

If your 8-bit AVR (Teensy 2) is running low on memory, using a smaller read_pins_t type saves SRAM.
Details are in config_key.h
*/
class PortWriteInterface
{
    public:
        virtual void write(const uint8_t pin, const bool level)=0;
};
#endif
