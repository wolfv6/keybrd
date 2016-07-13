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
        const uint8_t readPins;                  //bitwise pin configuration, 1 means read column
        uint8_t portState;                      //bitwise pin values, which is set in read()
    public:
        ReadPort(const uint8_t readPins): readPins(readPins), portState(0) {}

        //read port and store it's pins values in portState
        virtual uint8_t read()=0;
};
#endif
