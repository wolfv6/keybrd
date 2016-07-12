#ifndef ROWSCANNER_SHIFTREGS74HC165_H
#define ROWSCANNER_SHIFTREGS74HC165_H
#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <SPI.h>
#include <StrobePort.h>
#include <ReadPort.h>

/* Scanner_ShiftRegs74HC165 reads shift registers.
shift registers 74HC165 is Parallel-In-Serial-Out (PISO)
Upto 4 shift registers can be in a daisy chained.

In sketch:
    const uint8_t Scanner_ShiftRegs74HC165::SHIFT_LOAD = 10;
    call begin() from setup()

For active low:
    const bool Scanner_ShiftRegs74HC165::STROBE_ON = LOW;
    const bool Scanner_ShiftRegs74HC165::STROBE_OFF = HIGH;
    //shift register parallel input pins have 10k pull-down resistors powered
    //controller's MISO pin is connected to shift register's complementary serial output (/QH) pin

For active high:
    const bool Scanner_ShiftRegs74HC165::STROBE_ON = HIGH;
    const bool Scanner_ShiftRegs74HC165::STROBE_OFF = LOW;
    //shift register parallel input pins have 10k pull-down resistors grounded
    //controller's MISO pin is connected to shift register's serial output (QH) pin

In addition, each row needs to be connected to a strobe pin from controller.

 todo move this to tutorial
The shift register needs 5 wires.
The two parts of a split keyboard can be connected by one of:
 * eSATA cable (has 7 wires, good for 2 rows)
 * Ethernet cable (has 8 wires, good for 3 rows)

*/
class Scanner_ShiftRegs74HC165
{
    private:
        static const uint8_t SHIFT_LOAD;        //controller's pin number that is connected to shift register's SHIFT_LOAD pin
        static const bool STROBE_ON;            //logic level of strobe on, active state HIGH or LOW
        static const bool STROBE_OFF;           //logic level of strobe off, complement of active state
        const uint8_t STROBE_PIN;               //Arduino pin number connected to this row
        const uint8_t BYTE_COUNT;               //number of bytes to read from shift registers
        //uint8_t READ_PIN_COUNT;
    public:
        Scanner_ShiftRegs74HC165(const uint8_t STROBE_PIN, uint8_t READ_PIN_COUNT);
        virtual read_pins_t scan();
        void begin();
};
#endif
