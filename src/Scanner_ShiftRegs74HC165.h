#ifndef ROWSCANNER_SHIFTREGS74HC165_H
#define ROWSCANNER_SHIFTREGS74HC165_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <SPI.h>
#include <PortWrite.h>
#include <PortRead.h>

/* Scanner_ShiftRegs74HC165 reads shift registers.
shift registers 74HC165 are Parallel-In-Serial-Out (PISO)
Upto 4 shift registers can be in a daisy chained for a total of 32 read pins.

For active low:
Shift register parallel input pins have 10k pull-up resistors powered
Orient diodes with cathode (banded end) towards the write pins (row)
Controller's MISO pin is connected to shift register's complementary serial output (/QH) pin
Use these two lines in the sketch:
    const bool Scanner_ShiftRegs74HC165::STROBE_ON = LOW;
    const bool Scanner_ShiftRegs74HC165::STROBE_OFF = HIGH;

For active high:
Shift register parallel input pins have 10k pull-down resistors grounded
Orient diodes with cathode (banded end) towards the read pins.
Controller's MISO pin is connected to shift register's serial output (QH) pin
Use these two lines in the sketch:
    const bool Scanner_ShiftRegs74HC165::STROBE_ON = HIGH;
    const bool Scanner_ShiftRegs74HC165::STROBE_OFF = LOW;

In addition, each row needs to be connected to a strobe pin from the controller.
*/
class Scanner_ShiftRegs74HC165
{
    private:
        static const uint8_t SHIFT_LOAD;    //controller's pin number that is
                                            // connected to shift register's SHIFT_LOAD pin
        static const bool STROBE_ON;        //logic level of strobe on, active state HIGH or LOW
        static const bool STROBE_OFF;       //logic level of strobe off, complement of active state
        const uint8_t strobePin;            //Arduino pin number connected to this row
        const uint8_t byte_count;           //number of bytes to read from shift registers
    public:
        Scanner_ShiftRegs74HC165(const uint8_t strobePin, const uint8_t readPinCount);
        virtual read_pins_t scan();
        void begin();
};
#endif
