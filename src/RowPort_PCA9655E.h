#ifndef ROWPORT_PCA9655E_H
#define ROWPORT_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <RowPort.h>
#include "IOExpanderPort.h"

/* One PCA9655E I/O expander port connected to matrix rows.

begin() configures column port's configuration and output.
This should normally be called only once.

Instantiation
 ------------
Example instantiation for row port 0:
    IOExpanderPort port0(0, 0);
    RowPort_PCA9655E rowPort0(port0);

Example instantiation for row port 1:
    IOExpanderPort port1(1, 0);
    RowPort_PCA9655E rowPort1(port1);

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h

PCA9655E data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF
*/

class RowPort_PCA9655E : public RowPort
{
    private:
        IOExpanderPort& port;
        const uint8_t configurationByteCommand;
        const uint8_t outputByteCommand;

    public:
        //The constructor initialization list is in .cpp
        RowPort_PCA9655E(IOExpanderPort& port);
        void begin();

        virtual void setActivePinLow(const uint8_t activePin); //activePin is a port mask
        virtual void setActivePinHigh(const uint8_t activePin);
};
#endif
