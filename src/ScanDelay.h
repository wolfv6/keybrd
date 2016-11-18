#ifndef SCANDELAY_H
#define SCANDELAY_H
#include <Arduino.h>
#include <inttypes.h>

/* ScanDelay() delay's scan to give switches time to debounce.

DELAY_MICROSECONDS explained
----------------------------
A keyboard with a faster scan rate responds faster.
Follow these step to tune DELAY_MICROSECONDS for maximum scan rate for a given SAMPLE_COUNT:
Intantiate DELAY_MICROSECONDS in your sketch:
    ScanDelay scanDelay(1000);
Add this to the sketch's loop() function:
    debug.printMicrosecondsPerScan();
Compile and load the sketch into the microcontroller; microseconds_per_scan is printed every second.
Adjust the value of DELAY_MICROSECONDS and repeat until:
    debug.printMicrosecondsPerScan() <= DEBOUNCE_TIME / SAMPLE_COUNT

DEBOUNCE_TIME can be obtained from the switch's datasheet.  Some switch bounce times are:
Cherry MX specifies 5msec bounce time http://www.cherrycorp.com/english/switches/key/mx.htm
hasu measured Cherry MX bounce times .3ms to 1.4ms http://geekhack.org/index.php?topic=42385.0
Tactile switch MJTP series bounce 10 ms http://www.apem.com/files/apem/brochures/MJTP_6MM.pdf

The largest allowable DELAY_MICROSECONDS is 65535 (65.535 ms).

Avoid sampling the switch input at a rate synchronous to events in the environment
 that might create periodic EMI. For instance, 50 and 60 Hz.

Polling I2C may slow the scan rate enough so that no additional delay is needed
and scanDelay(0) can be omitted from the loop().

Could put delay directly in loop(), but then it's harder to finding this documentation.
    delay(5);
*/
class ScanDelay
{
    private:
        const unsigned int DELAY_MICROSECONDS; //delay each loop() for debouncing
    public:
        ScanDelay(const unsigned int DELAY_MICROSECONDS): DELAY_MICROSECONDS(DELAY_MICROSECONDS) {}
        void delay();
};
#endif
