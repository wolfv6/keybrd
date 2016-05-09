#ifndef MATRIX_H
#define MATRIX_H
#include <Arduino.h>
#include <inttypes.h>
#include "Row.h"

/*
Diode orientation
 ----------------
A keyboard's physically matrix is composed of rows and columns.
The rows and columns are physically connected to the keys.
The rows and columns are distinguishable by diode orientation (not horizontal/vertical).

For active low diode orientation is:
    cathodes on rows
    anodes on columns

For active high diode orientation is reversed:
    anodes on rows
    cathodes on columns

Pull-down resistors
 -------------------
If Matrix uses active low,  IC requires one pull-up resistor on each ColPort::colPins.
If Matrix uses active high, IC requires one pull-down resistor on each ColPort::colPins.
External pull-down resistors should have a value between 10k Ohms and 2.2k Ohms.
*/
class Matrix
{
    private:
        Row *const *const ptrsRows;         //array of row pointers
        const uint8_t rowCount;
        const bool activeHigh;              //logic level of strobe pin: 0=activeLow, 1=activeHigh

    public:
        Matrix( Row *const ptrsRows[], const uint8_t rowCount, const bool activeHigh)
            : ptrsRows(ptrsRows), rowCount(rowCount), activeHigh(activeHigh) {}

        void scan();
};
#endif
