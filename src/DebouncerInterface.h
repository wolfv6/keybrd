#ifndef DEBOUNCERINTERFACE_H
#define DEBOUNCERINTERFACE_H

/* DebouncerInterface is an interface class.
debounce() takes rawSignal and returns debounced signal.  Signals are bitwise.
*/
class DebouncerInterface
{
    public:
        virtual uint8_t debounce(const uint8_t rawSignal, uint8_t& debounced)=0;
};
#endif
