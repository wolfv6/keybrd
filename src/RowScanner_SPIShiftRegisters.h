#ifndef ROWSCANNER_SPI_SHIFTREGISTERS_H
#define ROWSCANNER_SPI_SHIFTREGISTERS_H
#include <Arduino.h>
#include <inttypes.h>
#include <SPI.h>
#include <RowScannerInterface.h>
#include <RowPort.h>
#include <ColPort.h>

/* RowScanner_SPIShiftRegisters reads all shift registers in a daisy chain.
//todo delete: Assumes only one row of shift registers is connected (no Slave Select).
*/
class RowScanner_SPIShiftRegisters : public RowScannerInterface
{
    private:
        const uint8_t SS;                       //Slave Select, pin on master
        const uint8_t BYTE_COUNT;               //number of shift registers
        const uint8_t KEY_COUNT;                //number of keys in row
    public:
        RowScanner_SPIShiftRegisters(const uint8_t SS, uint8_t BYTE_COUNT, uint16_t KEY_COUNT)
            : SS(SS), BYTE_COUNT(BYTE_COUNT), KEY_COUNT(KEY_COUNT) {}
        virtual uint8_t scan(uint16_t& rowEnd);
        void begin();
};
#endif
