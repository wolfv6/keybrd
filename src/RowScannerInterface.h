#ifndef ROWSCANNERINTERFACE_H
#define ROWSCANNERINTERFACE_H

#include <Arduino.h>
#include <inttypes.h>
#include <config_keybrd.h>

class RowScannerInterface
{
    public:
        virtual read_pins_t scan(read_pins_mask_t& rowEnd)=0;
};
#endif

