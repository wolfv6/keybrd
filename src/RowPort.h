#ifndef ROWPORT_H
#define ROWPORT_H
#include <Arduino.h>
#include <inttypes.h>

/*
RowPort is an abstract base class.
Port classes are the keybrd library's interface to microcontoller ports or I/O expander ports.
*/
class RowPort
{
    public:
        virtual void setActivePinHigh(const uint8_t activePin)=0;
        virtual void setActivePinLow(const uint8_t activePin)=0;
};
#endif
