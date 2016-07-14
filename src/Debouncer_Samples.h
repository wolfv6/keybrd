#ifndef DEBOUNCER_4SAMPLES_H
#define DEBOUNCER_4SAMPLES_H
#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>
#include <DebouncerInterface.h>

/* Debouncer_Samples
Configuration: #define SAMPLE_COUNT in config_keybrd.h
*/
class Debouncer_Samples : public DebouncerInterface
{
    private:
        read_pins_t samples[SAMPLE_COUNT];          //bitwise, one bit per key, most recent readings
        uint8_t samplesIndex;                   //samples[] current write index
    public:
        Debouncer_Samples(): samplesIndex(0) {}
        virtual read_pins_t debounce(const read_pins_t rawSignal, read_pins_t& debounced);
};
#endif

