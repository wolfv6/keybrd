#ifndef CODE_LAYERLOCK_H
#define CODE_LAYERLOCK_H

#include <inttypes.h>
#include <Code.h>
#include "LayerState.h"

/* Code_LayerLock calls LayerState when pressed to change activeLayer.
*/
class Code_LayerLock : public Code
{
    private:
        const uint8_t layer;
        LayerState& refLayerState;
    public:
        Code_LayerLock(const uint8_t layer, LayerState& refLayerState)
            : layer(layer), refLayerState(refLayerState) {}
        virtual void press();
        virtual void release();
};
#endif
