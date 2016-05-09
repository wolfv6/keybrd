#ifndef STATELAYERSINTERFACE_H
#define STATELAYERSINTERFACE_H

/* StateLayersInterface in an interface class
*/
class StateLayersInterface
{
    public:
        virtual uint8_t getActiveLayer()=0;
};
#endif
