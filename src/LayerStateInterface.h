#ifndef LAYERSTATEINTERFACE_H
#define LAYERSTATEINTERFACE_H

/* LayerStateInterface is an interface class
*/
class LayerStateInterface
{
    public:
        virtual uint8_t getActiveLayer()=0;
};
#endif
