#ifndef ROWSCANNER_SHIFTREGSREAD_H
#define ROWSCANNER_SHIFTREGSREAD_H

#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include "config_keybrd.h"
#include "ScannerInterface.h"

/* Scanner_ShiftRegsRead reads shift registers.
Upto 4 shift registers can be in a daisy chained for a total of 32 read pins.
This was tested on 74HC165 shift registers, which are Parallel-In-Serial-Out (PISO).

The row is always powered (there is no strobe that turns off).

Example instantiation:
    Row row_R0(scanner_R, 0, ptrsKeys_R0, sizeof(ptrsKeys_R0)/sizeof(*ptrsKeys_R0));
    Scanner_ShiftRegsRead scanner_R(HIGH, 6, 4);

In the above Row instantiation, argument 0 for "strobePin" is ignored because there is no strobe.

There are three Scanner_ShiftRegsRead-constructor parameters.
1. "activeState" paramter is ignored, but should be HIGH or LOW for documention.
   activeState is required by ScannerInterface.
   Actual activeState is determined by external pull-up or pull-down resistors described below.
2. "slaveSelect" paramter can be any controller pin connected to shift register's SHIFT-LOAD pin.
3. "byte_count" is the number of bytes to read from shift registers (1, 2, 3, or 4).
   byte_count should cover all the row's keys: byte_count*8 >= row's keyCount

Hardware setup:
The row of keys is connected to a controller by 5 wires:
* GND
* power
* CLK
* Slave Select
* MISO

Switches are connected to shift-register parallel-input pins and row.
Diodes are not needed if there is only one row.

For active low:
Shift-register parallel-input pins need 10k Ohm pull-up resistors powered.
Switches connect powered row to parallel-input pins.
Controller's MISO pin is connected to shift register's complementary serial output (/QH) pin

For active high:
Shift-register parallel-input pins need 10k pull-down resistors grounded.
Switches connect grouned row to parallel-input pins.
Controller's MISO pin is connected to shift register's serial output (QH) pin

If multiple rows (or any SPI divice) share a MISO line, the shift registers need to be isolated by a tri-state buffer chip. 
*/
class Scanner_ShiftRegsRead : public ScannerInterface
{
    private:
        const uint8_t slaveSelect;//controller pin number connected to shift register SHIFT-LOAD pin
        const uint8_t byte_count;               //number of bytes to read from shift registers
    public:
        Scanner_ShiftRegsRead(const bool activeState,
                                       const uint8_t slaveSelect, const uint8_t byte_count);
        void init(const uint8_t strobePin);
        void begin();
        virtual read_pins_t scan(const uint8_t strobePin);
};
#endif
