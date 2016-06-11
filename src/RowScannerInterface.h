#ifndef ROWSCANNERINTERFACE_H
#define ROWSCANNERINTERFACE_H

#include <Arduino.h>
#include <inttypes.h>

class RowScannerInterface
{
    public:
        virtual uint8_t scan(uint16_t& rowEnd)=0;
};
#endif

