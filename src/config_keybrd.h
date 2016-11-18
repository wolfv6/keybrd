#ifndef CONFIG_KEYBRD_H
#define CONFIG_KEYBRD_H
#include <inttypes.h>

/* This config_keybrd.h file is included by several keybrd library files.
If you change any values in this file, copy the entire library into your sketch folder,
and use double quotes to include the files in your sketch.
That way libary updates don't overwrite your changes.
 
The maximum number of pins scanned by RowScanner depends on size of read_pins_t.
By default, read_pins_t is set to uint32_t.
If your 8-bit AVR (Teensy 2) is running low on memory, using a smaller type saves SRAM.
Using smaller types on a 32-bit uC (Teensy LC) would accomplish nothing.

read_pins_t is used in:
    Row bit patterns
    ScannerInterface::scan()
     Scanner_ShiftRegsRead::scan()
     Scanner_ShiftRegsReadStrobed::scan()
     Scanner_uC::scan()
    DebouncerInterface::debounce()
     Debouncer_Samples::debounce()

Use a read_pins_t size that covers all read pins of all Scanner objects i.e.
    For Scanner_uC: read_pins_t bits >= Scanner_uC::readPinCount
    For Scanner_ShiftRegsRead: read_pins_t bits >= Scanner_ShiftRegsRead::byte_count * 8
   (For Scanner_IOE: I/O expanders are assumed to have 8 bits per port or less)
*/
//typedef uint8_t read_pins_t;
//typedef uint16_t read_pins_t;
typedef uint32_t read_pins_t;

/* SAMPLE_COUNT is used in Debouncer_Samples.h
SAMPLE_COUNT = 4 is very reliable for a keyboard.
Split keyboards with a long connecting wire or in environment with
strong electromagnetic interference (EMI) may need a larger SAMPLE_COUNT for reliability.
*/
const uint8_t SAMPLE_COUNT = 4; //number of consecutive equal bits needed to change a debounced bit

#endif
