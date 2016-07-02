#ifndef ROWSCANNER_SPI_SHIFTREGISTERS_H
#define ROWSCANNER_SPI_SHIFTREGISTERS_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_SPIShiftRegisters reads shift registers.
shift registers 74HC165 Parallel-In-Serial-Out (PISO)

in sketch:
    const uint8_t RowScanner_SPIShiftRegisters::SHIFT_LOAD = 10;
    call begin() from setup()

Upto 4 shift registers can be in a daisy chained.
The maximum keys per row is 31, because Arduino's largest type is 32 bits and rowEnd consumes the last bit.

The shift registers are active high:
    10k pull-down resistors are grounded
    connect controller's MISO pin to shift register's QH pin

The shift register needs 5 wires.
In addition, each row needs to be connected to a strobe pin from controller.
The two parts of a split keyboard can be connected by one of:
 * eSATA cable (has 7 wires, good for 2 rows)
 * Ethernet cable (has 8 wires, good for 3 rows)

*/
class RowScanner_SPIShiftRegisters : public RowScannerInterface
{
    private:
        static const uint8_t SHIFT_LOAD;        //controller's pin number that is connected to shift register's SHIFT_LOAD pin
        const uint8_t STROBE_PIN;               //Arduino pin number connected to this row
        const read_pins_mask_t ROW_END;         //bitwise, 1 bit marks positioned after last key of row
        const uint8_t BYTE_COUNT;               //number of bytes to read from shift registers
    public:
        RowScanner_SPIShiftRegisters(const uint8_t STROBE_PIN, uint8_t KEY_COUNT);
        virtual read_pins_t scan(read_pins_mask_t& rowEnd);
        void begin();
};
#endif
