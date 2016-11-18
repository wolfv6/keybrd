#ifndef CODE_LAYERLOCK_H
#define CODE_LAYERLOCK_H

#include <inttypes.h>
#include "Code.h"
#include "LayerState.h"

/* Code_LayerLock calls LayerState when pressed to change activeLayer.
*/
class Code_LayerLock : public Code
{
    private:
        const uint8_t layerId;
        LayerState& refLayerState;
    public:
        Code_LayerLock(const uint8_t layerId, LayerState& refLayerState)
            : layerId(layerId), refLayerState(refLayerState) {}
        virtual void press();
        virtual void release();
};
#endif
