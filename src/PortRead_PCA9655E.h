#ifndef PORTREAD_PCA9655E_H
#define PORTREAD_PCA9655E_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <PortReadInterface.h>
#include "PortIOE.h"

/* One PCA9655E I/O expander port connected to matrix columns.
PCA9655E does not have internal pull-up resistors (PCA9535E does).

Instantiation
 ------------
readPins parameter is bit pattern for port's pin configuration
    1=configure as input (for pins connected to column)
    0=configure as output (for LED or not connected to a column)
readPins are read from pin 0 on up.

Example instantiation for column port 1, with pins 2 and 3 connected to columns:
    const uint8_t PortIOE::DEVICE_ADDR = 0x20;      //PCA9655E address, all 3 ADDR pins are grounded
    PortIOE port1(1);
    PortRead_PCA9655E colPort1(port1, 1<<2 | 1<<3 );

Diode orientation
 ----------------
Diode orientation is explained in keybrd_library_user_guide.md > Diode orientation

PCA9655E data sheet
 ----------------
 http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF
*/
class PortRead_PCA9655E : public PortReadInterface
{
    private:
        PortIOE& port;
        const uint8_t readPins;                  //bit pattern, pin configuration, 1 means read pin
    public:
        PortRead_PCA9655E (PortIOE& port, const uint8_t readPins)
            : port(port), readPins(readPins) {}
        void begin(const uint8_t strobeOn);
        virtual uint8_t read();
};
#endif
