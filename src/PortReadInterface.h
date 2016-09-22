#ifndef PORTREADINTERFACE_H
#define PORTREADINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>

/*
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.
*/
class PortReadInterface
{
    public:
        virtual void begin(const uint8_t strobeOn)=0;
        virtual uint8_t read()=0;
};
#endif
