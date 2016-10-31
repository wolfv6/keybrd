#ifndef PORT_SHIFTREGS_H
#define PORT_SHIFTREGS_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <PortWriteInterface.h>

/* Port_ShiftRegs 
slaveSelect is controller-pin number connected to shift register RCLK pin a.k.a. SS or ST
*/
class Port_ShiftRegs : public PortWriteInterface
{
    private:
        const uint8_t slaveSelect;              //controller-pin number
        uint8_t outputVal;                      //bit pattern for LEDs
    public:
        Port_ShiftRegs(const uint8_t slaveSelect);
        void begin();
        void write(const uint8_t pin, const bool logicLevel);
};
#endif
