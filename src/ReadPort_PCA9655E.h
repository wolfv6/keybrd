#ifndef READPORT_PCA9655E_H
#define READPORT_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <ReadPort.h>
#include "IOEPort.h"

/* One PCA9655E I/O expander port connected to matrix columns.
PCA9655E does not have internal pull-up resistors (PCA9535E does).

Instantiation
 ------------
readPins parameter is port's bitwise pin configuration
    1=configure as input (for pins connected to column)
    0=configure as output (for LED or not connected to a column)

Example instantiation for column port 0, with pins 2 and 3 connected to columns:
    IOEPort port0(0, 0);
    ReadPort_PCA9655E colPort0(port0, 2<<0 | 1<<3 );
Example instantiation for column port 1, with pins 2 and 3 connected to columns:
    IOEPort port1(1, 0);
    ReadPort_PCA9655E colPort1(port1, 2<<0 | 1<<3 );

readPins are read from pin 0 on up.

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h
*/
class ReadPort_PCA9655E : public ReadPort
{
    private:
        IOEPort& port;
        const uint8_t configurationByteCommand;
        const uint8_t inputByteCommand;
    public:
        //The constructor initialization list is in .cpp
        ReadPort_PCA9655E(IOEPort& port, const uint8_t readPins);
        void begin();

        //read port and store result in portState
        virtual void read();
};
#endif
