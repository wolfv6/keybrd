/* debounce() function
Debounce uses multiple samples to debounces switch states,
where each sample contains the switch states for a row of switches, one bit per switch.

Debounce uses Dr. Marty's debounce algorithm from
 http://drmarty.blogspot.com.br/2009/05/best-switch-debounce-routine-ever.html
I2C and TWI protocols do not include any Packet Error Checking (PEC).
The goal of Marty's debounce routine is to reject spurious signals,
which is useful when connecting split keyboards with a cable using I2C or TWI.
Was tested on split keyboard with 3-meter long telephone wire to I/O expander

Dr. Marty's debounce algorithm:
 Periodically read samples and update the state when a number consecutive sample bits are equal.

Output from keybrd/examples/debounce_unit_test.cpp with SAMPLE_COUNT 4:
    button pressed:            100000001111111110000
    bouncy signal:             100001001111011110000
    debounced signal:          000000000001111111110
    isFallingEdge:             000000000000000000001
    isRisingEdge:              000000000001000000000
There is a latency equal to SAMPLE_COUNT, between button press and debounced signal.
 
samples[SAMPLE_COUNT] is a ring buffer.  samplesIndex is it's current write index.
SAMPLE_COUNT is the number of consecutive equal samples needed to debounce.
SAMPLE_COUNT is a macro because it defines samples[SAMPLE_COUNT] array size at compile time.
SAMPLE_COUNT should be at lease 1.

SAMPLE_COUNT = 4 is very reliable for a keyboard.
Keyboards with a long I2C wire or in environment with strong electromagnetic interference (EMI)
may need a larger SAMPLE_COUNT for reliability.
*/
#include "Debouncer_4Samples.h"

/* debounce() sets debounced and returns debouncedChanged.  All variables are bitwise.
For parameters, 1 means pressed, 0 means released.
For return, 1 means debounced changed.
*/
uint8_t Debouncer_4Samples::debounce(const uint8_t rawSignal, uint8_t& debounced)
{
    uint8_t previousDebounced;                  //bitwise, 1 means pressed, 0 means released
    uint8_t all_1 = ~0;                         //bitwise
    uint8_t all_0 = 0;                          //bitwise

    samples[samplesIndex] = rawSignal;          //insert rawSignal into samples[] ring buffer

    if (++samplesIndex >= SAMPLE_COUNT)         //if end of ring buffer
    {
        samplesIndex = 0;                       //wrap samplesIndex to beginning of ring buffer
    }

    for (uint8_t j = 0; j < SAMPLE_COUNT; j++)  //traverse the sample[] ring buffer
    {
        all_1 &= samples[j];                    //1 if all samples are 1
        all_0 |= samples[j];                    //0 if all samples are 0
    }

    previousDebounced = debounced;

    // update debounced if all the samples agree with one another
    // if all samples=1 then debounced=1
    //     elseif all samples=0 then debounced=0
    //         else debounced=previousDebounced i.e. no change
    debounced = all_1 | (all_0 & previousDebounced);

    return debounced xor previousDebounced;
}
