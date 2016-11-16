#ifndef PORTINTERFACE_H
#define PORTINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>
#include <PortWriteInterface.h>

/*
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.

Port classes that can read and write, inherit from PortInterface.
Port classes that can only write, inherit from PortWriteInterface.

write() interface emulates Arduino's digitalWrite().
*/
class PortInterface : public PortWriteInterface
{
    public:
        virtual void beginProtocol()=0;               //SPI bus or I2C bus
        virtual void begin(const uint8_t activeState)=0; //configure GPIO pins
        virtual void writeLow(const uint8_t pin)=0;
        virtual void writeHigh(const uint8_t pin)=0;
        virtual uint8_t read()=0;
};
#endif
