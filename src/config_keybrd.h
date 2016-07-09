#ifndef CONFIG_KEYBRD_H
#define CONFIG_KEYBRD_H
#include <inttypes.h>

/* size of read_pins_t depends on the maximum number of pins scanned by RowScanner.
By default, read_pins_t is set to the largest type.
If your 8-bit AVR is running low on memory, using a smaller type saves SRAM.
Using smaller types on a 32-bit uC (Teensy LC) would accomplish nothing.
*/

/* Uncomment a typedef read_pins_t size that covers all col pins of all RowScanner objects i.e.
    For RowScanner_PinsArray, RowScanner_PinsArray::READ_PIN_COUNT
    For RowScanner_SPIShiftRegisters, RowScanner_SPIShiftRegisters::KEY_COUNT
    For RowScanner_PinsBitwise, cover the last 1 bit in RowScanner_PinsBitwise::strobePin
*/
//typedef uint8_t read_pins_t;
//typedef uint16_t read_pins_t;
typedef uint32_t read_pins_t;

/* SAMPLE_COUNT = 4 is very reliable for a keyboard.
Split keyboards with a long connecting wire or in environment with
strong electromagnetic interference (EMI) may need a larger SAMPLE_COUNT for reliability.
SAMPLE_COUNT is used in Debouncer_Samples.h
*/
#define SAMPLE_COUNT 4      //number of consecutive equal bits needed to change a debounced bit

#endif
