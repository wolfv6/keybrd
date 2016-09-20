#ifndef CODE_LAYERHOLD_H
#define CODE_LAYERHOLD_H

#include <inttypes.h>
#include <Code.h>
#include "LayerState.h"

/* Code_LayerHold calls LayerState when pressed to change activeLayer.
*/
class Code_LayerHold : public Code
{
    private:
        const uint8_t layerId;
        LayerState& refLayerState;
    public:
        Code_LayerHold(const uint8_t layerId, LayerState& refLayerState)
            : layerId(layerId), refLayerState(refLayerState) {}
        virtual void press();
        virtual void release();
};
#endif
