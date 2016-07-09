#include "Debug.h"

void Debug::print_microseconds_per_scan()
{
    if (millis() >= nextTime)
    {
        Keyboard.print(1000000/scanCount);      //print microseconds per scan
        Keyboard.write(',');
        scanCount = 0;
        nextTime = millis() + 1000;             //print every second
    }
    scanCount++;
}
void Debug::print_scans_per_second()
{
    if (millis() >= nextTime)
    {
        Keyboard.print(scanCount);              //print scans per second
        Keyboard.write(',');
        scanCount = 0;
        nextTime = millis() + 1000;             //print every second
    }
    scanCount++;
}
