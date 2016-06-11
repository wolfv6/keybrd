#ifndef ROWIOE_H
#define ROWIOE_H

#include <RowBase.h>
#include <RowScanner_PinsBitwise.h>
#include <Debouncer_4Samples.h>

/* Row_DH_IOE is a row connected to an Input/Output Expander.

Configuration
-------------
Define and initilize DELAY_MICROSECONDS in sketch.  Detailed how to is in RowBase.cpp.

Instantiation
-------------
Example instantiation of a row:
    const uint8_t IOExpanderPort::ADDR = 0x18;

    IOExpanderPort port1(1, 0);
    RowPort_PCA9655E rowPort1(port1);

    IOExpanderPort port0(0, 0);
    ColPort_PCA9655E colPort0(port0, 1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 );

    Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row_IOE row_0(rowPort1, 1<<0, colPort0, ptrsKeys_0);

Number of pins in colPort0 should equal number of keys in ptrsKeys_0[] array.
    if a pin is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unprdictable way
*/
class Row_IOE : public RowBase
{
    private:
        RowScanner_PinsBitwise scanner;
        Debouncer_4Samples debouncer;
    public:
        Row_IOE( RowPort& refRowPort, const uint8_t strobePin,
             ColPort& refColPort, Key *const ptrsKeys[])
            : RowBase(ptrsKeys), scanner(refRowPort, strobePin, refColPort) { }
        uint8_t scan(uint16_t& rowEnd);
        uint8_t debounce(const uint8_t rowState, uint8_t& debounced);
};
#endif
