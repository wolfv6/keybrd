#ifndef STROBEPORT_PCA9655E_H
#define STROBEPORT_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <StrobePort.h>
#include "IOEPort.h"

/* One PCA9655E I/O expander port connected to matrix rows.

begin() configures column port's configuration and output.
This should normally be called only once.

Instantiation
 ------------
Example instantiation for row port 0:
    IOEPort port0(0, 0);
    StrobePort_PCA9655E rowPort0(port0);

Example instantiation for row port 1:
    IOEPort port1(1, 0);
    StrobePort_PCA9655E rowPort1(port1);

Diode orientation
 ----------------
PCA9655E does not have internal pull-up resistors, external pull-down resistors are required.

Rows, columns, and diode orientation are explained in Matrix.h

PCA9655E data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF
*/

class StrobePort_PCA9655E : public StrobePort
{
    private:
        IOEPort& port;
        const uint8_t configurationByteCommand;
        const uint8_t outputByteCommand;

    public:
        //The constructor initialization list is in .cpp
        StrobePort_PCA9655E(IOEPort& port);
        void begin();

        virtual void setActivePinLow(const uint8_t activePin); //activePin is a port mask todo delete
        virtual void setActivePinHigh(const uint8_t activePin); //todo delete also in StrobePort.h
        virtual void write(const uint8_t pin, const bool level);
};
#endif
