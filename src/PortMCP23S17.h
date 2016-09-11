#ifndef PORTMCP23S17_H
#define PORTMCP23S17_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>

class PortMCP23S17
{
    protected:
        void push(const uint8_t command, const uint8_t registerAddr, const uint8_t data);
};
#endif
