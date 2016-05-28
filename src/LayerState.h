#ifndef LAYERSTATE_H
#define LAYERSTATE_H

#include <inttypes.h>
#include <LayerStateInterface.h>

/* basic LayerState for keyboard.
When pressed, Code_Layer objects call LayerState functions lock() or hold().
When pressed, Layered objects call LayerState function getActiveLayer().
*/
class LayerState : public LayerStateInterface
{
    protected:
        uint8_t activeLayer;                    //currently active layer
        uint8_t lockedLayer;                    //most recently pressed lock layer
        virtual void setActiveLayer(const uint8_t layer);
    public:
        LayerState() : activeLayer(0), lockedLayer(0) {}
        virtual void hold(uint8_t layer);       //set activeLayer
        virtual void unhold(const uint8_t layer); //restore activeLayer to lockedLayer
        virtual void lock(uint8_t layer);       //set activeLayer and lock it
        virtual uint8_t getActiveLayer();
};
#endif
