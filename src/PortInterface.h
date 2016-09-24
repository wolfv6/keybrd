#ifndef PORTINTERFACE_H
#define PORTINTERFACE_H
#include <Arduino.h>
#include <inttypes.h>

/*
Port classes are the keybrd library's interface to microcontroller ports or I/O expander ports.
*/
class PortInterface
{
    public:
        virtual void beginProtocol()=0;               //SPI bus or I2C bus
        virtual void begin(const uint8_t strobeOn)=0; //configure GPIO pins
        virtual void write(const uint8_t strobePin, const bool pinLogicLevel)=0;
        virtual uint8_t read()=0;
};
#endif
