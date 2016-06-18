#ifndef COLPORT_MCP23018_H
#define COLPORT_MCP23018_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <ColPort.h>
#include "IOExpanderPort.h"

/* One MCP23018 I/O expander port connected to matrix columns.

Instantiation
 ------------
colPins parameter is port's bitwise pin configuration
    1=configure as input (for read)
    0=configure as output (for LED or not connected to a column)

example instantiation for column port A, with pins 2 and 3 connected to columnss:
    IOExpanderPort portA(0, ~0);
    ColPort_MCP23018 colPortA(portA, 1<<2 | 1<<3 );
example instantiation for column port B, with pins 2 and 3 connected to columns:
    IOExpanderPort portB(1, ~0);
    ColPort_MCP23018 colPortB(portB, 1<<2 | 1<<3 );

colPins are read from pin 0 on up.

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h

*/
class ColPort_MCP23018 : public ColPort
{
    private:
        IOExpanderPort& port;
        const uint8_t IODIR;                    //Input/Ouput Direction register
        const uint8_t GPIO;                     //General Purpose Input/Ouput register
        const uint8_t GPPU;                     //General Purpose Pullup register
    public:
        //The constructor initialization list is in .cpp
        ColPort_MCP23018(IOExpanderPort& port, const uint8_t colPins);
        void begin(uint8_t activeHigh);

        //read port and store result in portState
        virtual void read();
};
#endif
