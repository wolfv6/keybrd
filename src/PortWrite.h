#ifndef PORTWRITE_H
#define PORTWRITE_H
#include <Arduino.h>
#include <inttypes.h>

/*
PortWrite is an abstract base class.
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.
*/
class PortWrite
{
    public:
        virtual void write(const uint8_t pin, const bool level)=0;
};
#endif
