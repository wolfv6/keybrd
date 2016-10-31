#ifndef PORTWRITEINTERFACE_H
#define PORTWRITEINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>

/*
Port classes are the keybrd library's interface to MOSI shift registers i.e. Port_ShiftRegs

Port classes that can read & write, inherit from PortInterface.
Port classes that can only write, inherit from PortWriteInterface.
*/
class PortWriteInterface
{
    public:
        virtual void write(const uint8_t pin, const bool pinLogicLevel)=0;
};
#endif
