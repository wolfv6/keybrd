#ifndef DEBOUNCERINTERFACE_H
#define DEBOUNCERINTERFACE_H

#include "config_keybrd.h"

/*
debounce() takes rawSignal and returns debounced signal.  Signals are bit paterns.
*/
class DebouncerInterface
{
    public:
        virtual read_pins_t debounce(const read_pins_t rawSignal, read_pins_t& debounced)=0;
};
#endif
