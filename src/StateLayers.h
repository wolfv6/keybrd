#ifndef LAYERSTATE_H
#define LAYERSTATE_H

#include <inttypes.h>
#include <StateLayersInterface.h>
//#include <LED.h>

/* basic StateLayers for keyboard.
When pressed, Code_Layer objects call StateLayers functions lock() or hold().
When pressed, Layered objects call StateLayers function getActiveLayer().
*/
class StateLayers : public StateLayersInterface
{
    protected:
        uint8_t activeLayer;                    //currently active layer
        uint8_t lockedLayer;                    //most recently pressed lock layer
        virtual void setActiveLayer(const uint8_t layer);
    public:
        StateLayers() : activeLayer(0), lockedLayer(0) {}
        virtual void hold(uint8_t layer);               //set activeLayer
        virtual void unhold(const uint8_t layer);       //restore activeLayer to lockedLayer
        virtual void lock(uint8_t layer);               //set activeLayer and lock it
        virtual uint8_t getActiveLayer();
};
#endif
