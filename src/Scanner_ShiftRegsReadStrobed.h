#ifndef ROWSCANNER_SHIFTREGSREADSTROBED_H
#define ROWSCANNER_SHIFTREGSREADSTROBED_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <SPI.h>
#include <ScannerInterface.h>

/* Scanner_ShiftRegsReadStrobed reads shift registers.
Shift registers can be daisy chained for a total of 32 read pins.
This was tested on 74HC165 shift registers, which are Parallel-In-Serial-Out (PISO).

The class works with  machanical switches or photointerrupter switches.
A "strobe" powers the IR LEDs for a short time while the shift registers read the photo transistors.
The IR LEDs are off most of the time to preserve IR LED life.

Example instantiation:
    Scanner_ShiftRegsReadStrobed scanner_R(HIGH, 6, 4);

There are three Scanner_ShiftRegsReadStrobed parameters.
1. "activeState" paramter is active state HIGH or LOW.
2. "slaveSelect" paramter is controller pin connected to shift register's SHIFT-LOAD pin.
3. "byte_count" is the number of bytes to read from shift registers (1 to 4).
   byte_count should cover all the row's keys: byte_count*8 >= row's keyCount

Hardware setup:
Each row of keys is connected to a controller by 6 wires:
* GND
* power
* CLK
* Slave Select
* MISO
* strobe

For active low:
Shift-register parallel-input pins need 10k Ohm pull-up resistors powered.
Orient diodes with cathode (banded end) towards the write pins (row)
Controller's MISO pin is connected to shift register's complementary serial output (/QH) pin

For active high:
Shift-register parallel-input pins need 10k pull-down resistors grounded.
Orient diodes with cathode (banded end) towards the read pins.
Controller's MISO pin is connected to shift register's serial output (QH) pin

If multiple rows (or any SPI divice) share a MISO line, the shift registers need to be isolated by a tri-state buffer chip. 
*/
class Scanner_ShiftRegsReadStrobed : public ScannerInterface
{
    private:
        const bool activeState;                 //logic level of strobe on, active state HIGH or LOW
        const uint8_t slaveSelect;//controller pin number connected to shift register SHIFT-LOAD pin
        const uint8_t byte_count;               //number of bytes to read from shift registers
    public:
        Scanner_ShiftRegsReadStrobed(const bool activeState,
                                      const uint8_t slaveSelect, const uint8_t byte_count);
        virtual void init(const uint8_t strobePin);
        virtual read_pins_t scan(const uint8_t strobePin);
};
#endif
