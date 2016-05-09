#ifndef COLPORT_H
#define COLPORT_H
#include <Arduino.h>
#include <inttypes.h>

/*
ColPort is an abstract base class.
Port classes are the keybrd library's interface to microcontoller ports or I/O expander ports.
*/
class ColPort
{
    protected:
        const uint8_t colPins;                  //bitwise pin configuration, 1 means read column
        uint8_t portState;                      //bitwise pin values, which is set in read()
    public:
        ColPort(const uint8_t colPins): colPins(colPins), portState(0) {}

        //read port and store it's pins values in portState
        virtual void read()=0;
        uint8_t getColPins();
        uint8_t getPortState();
};
#endif
