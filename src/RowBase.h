#ifndef ROWBASE_H
#define ROWBASE_H
#include <Arduino.h>
#include <inttypes.h>
#include <Key.h>
#include <RowPort.h>
#include <ColPort.h>

/*
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

A keyboard with a faster scan rate is more resposive.
Follow these step to tune DELAY_MICROSECONDS for maximum scan rate within debounce times:
    Initialize DELAY_MICROSECONDS in your sketch:
        const unsigned int Row::DELAY_MICROSECONDS = 1000;
    Add this to the sketche's loop() function:
        keybrd.print_microseconds_per_scan();
    Compile and load the sketch into the microcontroller, which will print the actual microseconds_per_scan
    Incrementaly adjust the DELAY_MICROSECONDS untill the printed microseconds_per_scan is near the switches bounce time
A switche's debounce time can be obtained from the switche's datasheet
Cherry MX has 5ms bounce time http://www.cherrycorp.com/english/switches/key/mx.htm
hasu measured Cherry MX bounce times .3ms to 1.4ms http://geekhack.org/index.php?topic=42385.0
Tactile switch MJTP series bounce 10 ms http://www.apem.com/files/apem/brochures/MJTP_6MM.pdf
Optic switches 0 bounce time because optic doesn't bounce

Slow-scan trick for debug message that print too fast
    Keyboard.print(F("debug message"));
Change DELAY_MICROSECONDS to a large number like 10000
That way printing debug messages is slowed to a managable rate
*/
class RowBase
{
    private:
        Key *const *const ptrsKeys;         //array of Key pointers

        RowPort &refRowPort;                //this row's IC port
        const uint8_t rowPin;               //bitwise, 1 indicates IC pin connected to this row

        ColPort *const *const ptrsColPorts; //array of column ports
        const uint8_t colPortCount;

        void scan(const bool activeHigh);
        uint8_t getRowState(uint16_t& rowEnd, const bool activeHigh);
        virtual uint8_t debounce(const uint8_t rowState)=0; //debouncer and I2C error correction
        void detectEdge(uint8_t newDebounced, uint8_t& isFallingEdge, uint8_t& isRisingEdge);
        void pressRelease(const uint16_t rowEnd,
                const uint8_t isFallingEdge, const uint8_t isRisingEdge);
        virtual void keyWasPressed();
    protected:
        uint8_t debounced;                  //bitwise, one bit per key, debounced value of readings
    public:
        RowBase( RowPort &refRowPort, const uint8_t rowPin,
            ColPort *const ptrsColPorts[], const uint8_t colPortCount,
            Key *const ptrsKeys[])
            : ptrsKeys(ptrsKeys), refRowPort(refRowPort), rowPin(rowPin),
              ptrsColPorts(ptrsColPorts), colPortCount(colPortCount),
              debounced(0) { }
        //Key* getPtrKey(uint8_t col) const; todo delete, no longer needed 5/31/16
        void process(const bool activeHigh);
};
#endif
