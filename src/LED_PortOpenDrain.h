#ifndef LED_PORT_H
#define LED_PORT_H
#include <Arduino.h>
#include <inttypes.h>
#include "LEDInterface.h"
#include "PortWriteInterface.h"

/* An LED_PortOpenDrain object is an I/O expander ouput pin that is connected to an LED.
LED_PortOpenDrain functions turn LED on and off.
LED anode connected to power.  LED cathode connected to open-drain ouput pin.

This class is for open drain ouput pins.
For LEDs connected to push-pull output types, use LED_Port class.

Example initialization:
    const uint8_t IOE_ADDR = 0x20;
    Port_MCP23S17 portA(IOE_ADDR, 0, 1<<0 | 1<<1 );
    LED_PortOpenDrain LED_fn(portA, 1<<5);

Example initialization:
    Port_ShiftRegs shiftRegs(8);
    LED_PortOpenDrain LED_fn(shiftRegs, 1<<6);
    
*/
class LED_PortOpenDrain : public LEDInterface
{
    private:
        PortWriteInterface& refPort;
        const uint8_t pin;                      //bit pattern, 1 is pin connected to LED

    public:
        LED_PortOpenDrain(PortWriteInterface& refPort, const uint8_t pin)
            : refPort(refPort), pin(pin) {}
        virtual void on();
        virtual void off();
};
#endif
