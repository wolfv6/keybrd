#ifndef LED_MCP23018_H
#define LED_MCP23018_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <LED.h>
#include "IOExpanderPort.h"

/* Class LED_MCP23018 uses a MCP23018 I/O expander pin to turn a LED on and off.

Connect the LED in series with the resistor:
    determin resistor value needed (Internet search: LED resistor value)
    Connect the LED's (-) ground to the AVR output pin
    connect LED's (+) to power
Never connect a LED directly from ground to power.  Doing so would destroy the LED.

MCP23018 ouput is open drain.  The output acts like a switch to ground.
It cannot produce a high signal by itself.
*/
class LED_MCP23018: public LED
{
    private:
        IOExpanderPort& port;
        const uint8_t GPIO;                     //General Purpose Input/Ouput register address
        const uint8_t pin;                      //bitwise pin to LED

    public:
        LED_MCP23018(IOExpanderPort& port, const uint8_t pin)
            : port(port), GPIO(port.num + 0x12), pin(pin) {}

        virtual void on();

        virtual void off();
};
#endif
