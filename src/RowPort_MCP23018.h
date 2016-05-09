#ifndef ROWPORT_MCP23018_H
#define ROWPORT_MCP23018_H
#include <Arduino.h>
#include <inttypes.h>
#include <Wire.h>
#include <RowPort.h>
#include "IOExpanderPort.h"

/* One MCP23018 I/O expander port connected to matrix rows.

begin() configures column port's IODIR, GPIO.
This should normally be called only once.

Instantiation
 ------------
Example instantiation for row port A:
    IOExpanderPort portA(0, ~0);
    RowPort_MCP23018 rowPortA(portA);
Example instantiation for row port B:
    IOExpanderPort portB(1, ~0);
    RowPort_MCP23018 rowPortB(portB);

Diode orientation
 ----------------
Rows, columns, and diode orientation are explained in Matrix.h

MCP23018 data sheet
 ------------------
 http://ww1.microchip.com/downloads/en/DeviceDoc/22103a.pdf
*/
class RowPort_MCP23018 : public RowPort
{
    private:
        IOExpanderPort& port;
        const uint8_t IODIR;                    //Input/Ouput Direction register address
        const uint8_t GPIO;                     //General Purpose Input/Ouput register address

    public:
        //The constructor initialization list is in .cpp
        RowPort_MCP23018(IOExpanderPort& port);
        void begin();

        virtual void setActivePinLow(const uint8_t activePin); //activePin is a port mask
        virtual void setActivePinHigh(const uint8_t activePin);
};
#endif
