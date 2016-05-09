#ifndef CODE_LAYERHOLD_H
#define CODE_LAYERHOLD_H

#include <inttypes.h>
#include <Code.h>
#include "StateLayers.h"

/* Code_LayerHold calls StateLayers when pressed to change activeLayer.
*/
class Code_LayerHold : public Code
{
    private:
        const uint8_t layer;
        StateLayers& refStateLayers;
    public:
        Code_LayerHold(const uint8_t layer, StateLayers& refStateLayers)
            : layer(layer), refStateLayers(refStateLayers) {}
        virtual void press();
        virtual void release();
};
#endif
