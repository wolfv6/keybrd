#ifndef PORTWRITE_PCA9655E_H
#define PORTWRITE_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <PortWrite.h>
#include "PortIOE.h"

/* One PCA9655E I/O expander port connected to matrix rows.

begin() configures column port's configuration and output.
This should normally be called only once.

If PortRead_PCA9655E is instantiated on the same port, do not use PortWrite_PCA9655E::begin().
Use PortRead_PCA9655E::begin() instead.  Otherwise READ_PINS could be overwritten.

Instantiation
 ------------
Example instantiation for row port 0:
    PortIOE port0(0, 0);
    PortWrite_PCA9655E rowPort0(port0);

Example instantiation for row port 1:
    PortIOE port1(1, 0);
    PortWrite_PCA9655E rowPort1(port1);

Diode orientation
 ----------------
PCA9655E does not have internal pull-up resistors, external pull-down resistors are required.

Rows, columns, and diode orientation are explained in Matrix.h

PCA9655E data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF
*/

class PortWrite_PCA9655E : public PortWrite
{
    private:
        PortIOE& port;
        const uint8_t configurationByteCommand;
        const uint8_t outputByteCommand;

    public:
        //The constructor initialization list is in .cpp
        PortWrite_PCA9655E(PortIOE& port);
        void begin();

        virtual void write(const uint8_t pin, const bool level);
};
#endif
