#ifndef IOEXPANDERPORT_H
#define IOEXPANDERPORT_H
#include <inttypes.h>

/* The pins of an IC's port can be split between RowPort, ColPort, and LED.

IOExpanderPort contains outputVal, the value of a port's output register.
outputVal is used for port manipulation by classes RowPort and LED.
One port's outputVal can be shared by one RowPort object and multiple LED objects.

IOExpanderPort is only used by I/O expander port classes.
AVR port classes do not need a similar class because PORTx is global in the Arduino library.

Instantiation
 ------------
Example IOExpanderPort::ADDR initilization:
    const uint8_t IOExpanderPort::ADDR = 0x18;
Be careful with the ADDR.
Table 6 in PCA9655E datasheet lists 8-bit versions of I2C addresses.
The Arduino Wire library uses 7-bit addresses throughout, so drop the low bit.
For example, I2C address with AD2=GND AD1=SCL AD0=SCL,
    Table 6 lists      8-bit ADDR = 0x30 (b 00110000)
    while Arduino uses 7-bit ADDR = 0x18 (b 00011000)
http://playground.arduino.cc/Main/WireLibraryDetailedReference
The PCA9655E data sheet is on http://www.onsemi.com/pub_link/Collateral/PCA9655E-D.PDF

portNumber: If the I/O expander uses port letters, use 0 instead of A, use 1 instead of B.
outputVal: For pins that are connected to active low rows, set outputVal bit to 1.
           Set all other outputVal bits to 0.

Example instantiation for port0 with active low rows on all pins:
    IOExpanderPort port0(0, ~0);

Example instantiation for portA with active low rows on pins 0,1,2:
    IOExpanderPort portA(0, 1<<0 | 1<<1 | 1<<2 );

Example instantiation for portB with active high rows on pins 0,1,2:
    IOExpanderPort portB(1, 0);
*/
struct IOExpanderPort
{
    static const uint8_t ADDR;                  //I2C address
    const uint8_t num;                          //port number
    uint8_t outputVal;                          //bitwise value of output register

    IOExpanderPort(const uint8_t portNumber, uint8_t outputVal)
        : num(portNumber), outputVal(outputVal) {}
};
#endif
