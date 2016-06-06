#ifndef ROWSCANNER_BITMANIPULATION_H
#define ROWSCANNER_BITMANIPULATION_H
#include <Arduino.h>
#include <inttypes.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

class RowScanner_BitManipulation : public RowScannerInterface
{
    private:
        static const bool activeHigh;       //logic level of strobe pin: 0=activeLow, 1=activeHigh
        RowPort &refRowPort;                //this row's IC port
        const uint8_t rowPin;               //bitwise, 1 indicates IC pin connected to this row

        ColPort *const *const ptrsColPorts; //array of column ports
        const uint8_t colPortCount;

    public:
        RowScanner_BitManipulation(RowPort &refRowPort, const uint8_t rowPin,
            ColPort *const ptrsColPorts[], const uint8_t colPortCount)
            : refRowPort(refRowPort), rowPin(rowPin),
              ptrsColPorts(ptrsColPorts), colPortCount(colPortCount) {}
        virtual uint8_t scan(uint16_t& rowEnd);
        uint8_t getRowState(uint16_t& rowEnd);
};
#endif
