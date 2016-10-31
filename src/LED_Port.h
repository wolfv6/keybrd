#ifndef LED_PORT_H
#define LED_PORT_H
#include <Arduino.h>
#include <inttypes.h>
#include <LEDInterface.h>
#include <PortWriteInterface.h>

/* An LED_Port object is an I/O expander pin that is connected to an LED indicator light.
LED_Port functions turn LED on and off.

Example initialization:
    const uint8_t IOE_ADDR = 0x20;
    Port_MCP23S17 portA(IOE_ADDR, 0, 1<<0 | 1<<1 );
    LED_Port LED_fn(portA, 1<<5);

Example initialization:
    Port_ShiftRegs shiftRegs(8);
    LED_Port LED_fn(shiftRegs, 1<<6);
    
*/
class LED_Port : public LEDInterface
{
    private:
        PortWriteInterface& refPort;
        const uint8_t pin;                      //bit pattern, 1 is pin connected to LED

    public:
        LED_Port(PortWriteInterface& refPort, const uint8_t pin)
            : refPort(refPort), pin(pin) {}
        virtual void on();
        virtual void off();
};
#endif
