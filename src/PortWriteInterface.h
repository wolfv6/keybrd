#ifndef PORTWRITEINTERFACE_H
#define PORTWRITEINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>

class PortWriteInterface
{
    public:
        virtual void write(const uint8_t pin, const bool pinLogicLevel)=0;
};
#endif
