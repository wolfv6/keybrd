#ifndef CONFIG_KEYBRD_H
#define CONFIG_KEYBRD_H
#include <inttypes.h>

/* size of read_pins_t depends on the maximum number of pins scanned by RowScanner.
By default, read_pins_t is set to the largest type.
If your 8-bit AVR (Teensy 2) is running low on memory, using a smaller type saves SRAM.
Using smaller types on a 32-bit uC (Teensy LC) would accomplish nothing.
*/

/* Use a read_pins_t size that covers all read pins of all Scanner objects i.e.
    For Scanner_uC: read_pins_t bits >= Scanner_uC::readPinCount
    For Scanner_ShiftRegsPISO: read_pins_t bits >= Scanner_ShiftRegsPISO::byte_count * 8
   (For Scanner_IOE: I/O expanders are assumed to have 8 bits per port or less)
*/
//typedef uint8_t read_pins_t;
//typedef uint16_t read_pins_t;
typedef uint32_t read_pins_t;

/* SAMPLE_COUNT_MACRO is used in Debouncer_Samples.h
SAMPLE_COUNT_MACRO = 4 is very reliable for a keyboard.
Split keyboards with a long connecting wire or in environment with
strong electromagnetic interference (EMI) may need a larger SAMPLE_COUNT_MACRO for reliability.
*/
#define SAMPLE_COUNT_MACRO 4      //number of consecutive equal bits needed to change a debounced bit

#endif
