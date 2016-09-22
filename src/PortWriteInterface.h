#ifndef PORTWRITEINTERFACE_H
#define PORTWRITEINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>

/*
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.
*/
class PortWriteInterface
{
    public:
        virtual void begin()=0;
        virtual void write(const uint8_t strobePin, const bool pinLogicLevel)=0;
};
#endif
