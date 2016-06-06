#ifndef ROWSCANNERINTERFACE_H
#define ROWSCANNERINTERFACE_H

/* RowScannerInterface is an interface class.
Sets rowEnd and returns rowState.
rowEnd is bitwise, where 1 bit corrsiponds to place immediatly after last key of row.
rowEnd and rowMask are larger type than portMask so that they can not overflow.
*/
#include <Arduino.h>
#include <inttypes.h>

class RowScannerInterface
{
    public:
        virtual uint8_t scan(uint16_t& rowEnd)=0;
};
#endif

