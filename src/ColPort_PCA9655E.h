#ifndef COLPORT_PCA9655E_H
#define COLPORT_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <ColPort.h>
#include "IOExpanderPort.h"

/* One PCA9655E I/O expander port connected to matrix columns.
PCA9655E does not have internal pull-up resistors (PCA9535E does).

Instantiation
 ------------
colPins parameter is port's bitwise pin configuration
    1=configure as input (for pins connected to column)
    0=configure as output (for LED or not connected to a column)

Example instantiation for column port 0, with pins 2 and 3 connected to columns:
    IOExpanderPort port0(0, 0);
    ColPort_PCA9655E colPort0(port0, 2<<0 | 1<<3 );
Example instantiation for column port 1, with pins 2 and 3 connected to columns:
    IOExpanderPort port1(1, 0);
    ColPort_PCA9655E colPort1(port1, 2<<0 | 1<<3 );

colPins are read from pin 0 on up.

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h
*/
class ColPort_PCA9655E : public ColPort
{
    private:
        IOExpanderPort& port;
        const uint8_t configurationByteCommand;
        const uint8_t inputByteCommand;
    public:
        //The constructor initialization list is in .cpp
        ColPort_PCA9655E(IOExpanderPort& port, const uint8_t colPins);
        void begin();

        //read port and store result in portState
        virtual void read();
};
#endif
