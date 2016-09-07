#ifndef ROWSCANNER_SHIFTREGS74HC165_H
#define ROWSCANNER_SHIFTREGS74HC165_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <SPI.h>
#include <ScannerInterface.h>
#include <PortWriteInterface.h>
#include <PortReadInterface.h>

/* Scanner_ShiftRegs74HC165 reads shift registers.
shift registers 74HC165 are Parallel-In-Serial-Out (PISO)
Upto 4 shift registers can be in a daisy chained for a total of 32 read pins.

For active low:
Shift register parallel input pins have 10k pull-up resistors powered
Orient diodes with cathode (banded end) towards the write pins (row)
Controller's MISO pin is connected to shift register's complementary serial output (/QH) pin
Use these two lines in the sketch:
    const bool Scanner_ShiftRegs74HC165::strobeOn = LOW;
    const bool Scanner_ShiftRegs74HC165::strobeOff = HIGH;

For active high:
Shift register parallel input pins have 10k pull-down resistors grounded
Orient diodes with cathode (banded end) towards the read pins.
Controller's MISO pin is connected to shift register's serial output (QH) pin
Use these two lines in the sketch:
    const bool Scanner_ShiftRegs74HC165::strobeOn = HIGH;
    const bool Scanner_ShiftRegs74HC165::strobeOff = LOW;

In addition, each row needs to be connected to a strobe pin from the controller.
*/
class Scanner_ShiftRegs74HC165 : public ScannerInterface
{
    private:
        const bool strobeOn;         //logic level of strobe on, active state HIGH or LOW
        const bool strobeOff;        //logic level of strobe off, complement of active state
        const uint8_t slaveSelect;    //controller's pin number that is
                                            // connected to shift register's SHIFT-LOAD pin
        const uint8_t byte_count;           //number of bytes to read from shift registers
    public:
        Scanner_ShiftRegs74HC165(const bool strobeOn, const uint8_t slaveSelect,
                const uint8_t readPinCount);
        void init(const uint8_t strobePin);
        void begin();
        virtual read_pins_t scan(const uint8_t strobePin);
};
#endif
