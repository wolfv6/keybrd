#ifndef PORTWRITE_PCA9655E_H
#define PORTWRITE_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <PortWriteInterface.h>
#include "PortIOE.h"

/* One PCA9655E I/O expander port connected to matrix rows.
write() can output logiclevel to strobePin, one LED pin, or multiple pins.

Instantiation
 ------------
Example instantiation:
    const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //PCA9655E address, all 3 ADDR pins are grounded
    PortIOE port0(0);
    PortWrite_PCA9655E rowPort0(port0);

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

PCA9655E data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF
*/

class PortWrite_PCA9655E : public PortWriteInterface
{
    private:
        PortIOE& port;
    public:
        PortWrite_PCA9655E(PortIOE& port) : port(port) {}
        void begin();

        virtual void write(const uint8_t pin, const bool logicLevel);
};
#endif
