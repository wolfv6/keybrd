#ifndef READPORT_H
#define READPORT_H
#include <Arduino.h>
#include <inttypes.h>

/*
ReadPort is an abstract base class.
Port classes are the keybrd library's interface to microcontoller ports or I/O expander ports.
*/
class ReadPort
{
    protected:
        const uint8_t READ_PINS;                  //bitwise pin configuration, 1 means read column
    public:
        ReadPort(const uint8_t READ_PINS): READ_PINS(READ_PINS) {}

        //read port and return readState
        virtual uint8_t read()=0;
};
#endif
