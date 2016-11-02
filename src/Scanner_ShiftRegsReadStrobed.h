#ifndef ROWSCANNER_SHIFTREGSPISOMULTIROW_H
#define ROWSCANNER_SHIFTREGSPISOMULTIROW_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <SPI.h>
#include <ScannerInterface.h>

/* Scanner_ShiftRegsReadStrobed reads shift registers.
This was tested on 74HC165 shift registers, which are Parallel-In-Serial-Out (PISO).
Shift registers can be daisy chained for a total of 32 read pins.

Example instantiation:
    Scanner_ShiftRegsReadStrobed scanner_R(HIGH, SS, 4);

There are three Scanner_ShiftRegsReadStrobed parameters.
"strobeOn" paramter is active state HIGH or LOW.

"slaveSelect" paramter can be any controller pin connected to shift register's SHIFT-LOAD pin.

"byte_count" is the number of bytes to read from shift registers (1 to 4).
byte_count should cover all the row's keys:
    byte_count*8 >= row's keyCount

Hardware setup:
Each row needs to be connected to a strobe pin from the controller.
Switch and diode in series, connect shift-register parallel-input pins to strobed row.

For active low:
Shift-register parallel-input pins need 10k Ohm pull-up resistors powered.
Orient diodes with cathode (banded end) towards the write pins (row)
Controller's MISO pin is connected to shift register's complementary serial output (/QH) pin

For active high:
Shift-register parallel-input pins need 10k pull-down resistors grounded.
Orient diodes with cathode (banded end) towards the read pins.
Controller's MISO pin is connected to shift register's serial output (QH) pin
*/
class Scanner_ShiftRegsReadStrobed : public ScannerInterface
{
    private:
        const bool strobeOn;                    //logic level of strobe on, active state HIGH or LOW
        const bool strobeOff;                   //logic level of strobe off, complement of strobeOn
        const uint8_t slaveSelect;//controller pin number connected to shift register SHIFT-LOAD pin
        const uint8_t byte_count;               //number of bytes to read from shift registers
    public:
        Scanner_ShiftRegsReadStrobed(const bool strobeOn,
                                      const uint8_t slaveSelect, const uint8_t byte_count);
        virtual void init(const uint8_t strobePin);
        virtual void begin();
        virtual read_pins_t scan(const uint8_t strobePin);
};
#endif
