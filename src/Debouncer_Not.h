#ifndef DEBOUNCER_NOT_H
#define DEBOUNCER_NOT_H
#include <Arduino.h>
#include <inttypes.h>
#include "config_keybrd.h"
#include "DebouncerInterface.h"

/* Debouncer_Not does not debounce.
debounce() returns raw signal, no debouncing is performed.

A keyboard does not need a debouncing if one of the following is true:
    * keypad has hardware debouncers
    * poling I2C makes scan rate slower than debounce time
    * optic switches are used (because they don't bounce)
*/
class Debouncer_Not : public DebouncerInterface
{
    public:
        virtual read_pins_t debounce(const read_pins_t rawSignal, read_pins_t& debounced);
};
#endif
