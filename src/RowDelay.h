#ifndef ROWDELAY_H
#define ROWDELAY_H
#include <Arduino.h>
#include <inttypes.h>

/* RowDelay() delay's scan to give switches time to debounce.
For fastest response time, RowDelay() should be placed before scan() or after pressRelease()
 (RowDelay() between scan and send would unnecessarily delay send).

DELAY_MICROSECONDS explained
----------------------------
A keyboard with a faster scan rate responds faster.
Follow these step to tune DELAY_MICROSECONDS for maximum scan rate for a given SAMPLE_COUNT:
Initialize DELAY_MICROSECONDS in your sketch:
    const unsigned int RowDelay::DELAY_MICROSECONDS = 1000;
Add this to the sketch's loop() function:
    debug.print_microseconds_per_scan();
Compile and load the sketch into the microcontroller; microseconds_per_scan is printed every second.
Adjust the value of DELAY_MICROSECONDS and repeat until:
    debug.print_microseconds_per_scan() <= DEBOUNCE_TIME / SAMPLE_COUNT

DEBOUNCE_TIME can be obtained from the switch's datasheet.  Some switch bounce times are:
Cherry MX specifies 5msec bounce time http://www.cherrycorp.com/english/switches/key/mx.htm
hasu measured Cherry MX bounce times .3ms to 1.4ms http://geekhack.org/index.php?topic=42385.0
Tactile switch MJTP series bounce 10 ms http://www.apem.com/files/apem/brochures/MJTP_6MM.pdf 

Avoid sampling the switch input at a rate synchronous to events in the environment
 that might create periodic EMI. For instance, 50 and 60 Hz.

The largest allowable DELAY_MICROSECONDS is 65535 (.065535 seconds).

Polling I2C may slow the scan rate enough so that no additional delay is needed:
    const unsigned int RowDelay::DELAY_MICROSECONDS = 0;

DELAY_MICROSECONDS is static so multiple row types can share it.
For example, primary and secondary matrices would share the same DELAY_MICROSECONDS.
*/
class RowDelay
{
    private:
        static const unsigned int DELAY_MICROSECONDS; //delay between each Row scan for debouncing
    public:        
        void delay();
};
#endif
