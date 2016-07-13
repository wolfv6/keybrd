#ifndef STROBEPORT_H
#define STROBEPORT_H
#include <Arduino.h>
#include <inttypes.h>

/*
StrobePort is an abstract base class.
Port classes are the keybrd library's interface to microcontoller ports or I/O expander ports.
*/
class StrobePort
{
    public:
        virtual void write(const uint8_t pin, const bool level)=0;
};
#endif
