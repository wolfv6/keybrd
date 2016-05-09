#ifndef CODE_LAYERLOCK_H
#define CODE_LAYERLOCK_H

#include <inttypes.h>
#include <Code.h>
#include "StateLayers.h"

/* Code_LayerLock calls StateLayers when pressed to change activeLayer.
*/
class Code_LayerLock : public Code
{
    private:
        const uint8_t layer;
        StateLayers& refStateLayers;
    public:
        Code_LayerLock(const uint8_t layer, StateLayers& refStateLayers)
            : layer(layer), refStateLayers(refStateLayers) {}
        virtual void press();
        virtual void release();
};
#endif
