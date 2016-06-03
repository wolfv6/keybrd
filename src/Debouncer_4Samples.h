#ifndef DEBOUNCER_4SAMPLES_H
#define DEBOUNCER_4SAMPLES_H
#include <Arduino.h>
#include <inttypes.h>
#include <DebouncerInterface.h>

#define SAMPLE_COUNT 4      //number of consecutive equal bits needed to change a debounced bit

/* Debouncer_4Samples
Configuration: #define SAMPLE_COUNT in this header file.
*/
class Debouncer_4Samples : public DebouncerInterface
{
    private:
        uint8_t samples[SAMPLE_COUNT];          //bitwise, one bit per key, most recent readings
        uint8_t samplesIndex;                   //samples[] current write index
    public:
        Debouncer_4Samples(): samplesIndex(0) {}
        virtual uint8_t debounce(const uint8_t rawSignal, uint8_t& debounced);
};
#endif

