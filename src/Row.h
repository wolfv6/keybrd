#ifndef ROW_H
#define ROW_H

#include <RowBase.h>

#define SAMPLE_COUNT 4      //number of consecutive equal bits needed to change a debounced bit

/*
Configuration
-------------
#define SAMPLE_COUNT in this header file.
define and initilize DELAY_MICROSECONDS in sketch.
    const unsigned int Row::DELAY_MICROSECONDS = 0;

Instantiation
 ------------
Example instantiation of a row:
    RowPort_AVR rowPortF(DDRF, PORTF);

    ColPort_AVR colPortB(DDRB, PORTB, PINB, 1<<0 | 1<<1 | 1<<2 | 1<<3 );
    ColPort_AVR colPortD(DDRD, PORTD, PIND, 1<<2 | 1<<3 );

    ColPort* const ptrsColPorts[] = { &colPortB, &colPortD };
    const uint8_t COL_PORTS_COUNT = sizeof(ptrsColPorts)/sizeof(*ptrsColPorts);

    const PROGMEM Key* const ptrsKeys_0[] = { &k_00, &k_01, &k_02, &k_03, &k_04, &k_05 };
    Row row_0(ptrsKeys_0, &rowPortF, 1<<0, ptrsColPorts, COL_PORTS_COUNT);

Number of ColPort::colPins should equal number of keys in Row::ptrsKeys array
    if a pin is missing, a key will be unresposive
    if a Key pointer is missing, the keyboard will fail in an unprdictable way
*/
class Row : public RowBase
{
    private:
        uint8_t samples[SAMPLE_COUNT];          //bitwise, one bit per key, most recent readings
        uint8_t samplesIndex;                   //samples[] current write index
        virtual uint8_t debounce(const uint8_t rowState);
    public:
        Row( RowPort &refRowPort, const uint8_t rowPin,
            ColPort *const ptrsColPorts[], const uint8_t colPortCount, Key *const ptrsKeys[])
            : RowBase(refRowPort, rowPin, ptrsColPorts, colPortCount, ptrsKeys), samplesIndex(0) { }
};
#endif
