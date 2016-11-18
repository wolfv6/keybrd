#ifndef CODE_LAYERHOLDSHIFT_H
#define CODE_LAYERHOLDSHIFT_H

#include <inttypes.h>
#include "Code.h"
#include "LayerState.h"
#include "Code_Shift.h"

/* Code_LayerHoldShift calls LayerState when pressed to change activeLayer.
When a Code_LayerHoldShift object is pressed or released, it:
  * sends scancode in refCodeShift
  * calls LayerState to change activeLayer

Codes defined in sketch would be Code_Sc and Code_ScNS
(Code_ScS is not need because refCodeShift sends the shift scancode).
*/
class Code_LayerHoldShift : public Code
{
    private:
        const uint8_t layerId;
        LayerState& refLayerState;
        Code_Shift& refCodeShift;
    public:
        Code_LayerHoldShift(const uint8_t layerId, LayerState& refLayerState,
              Code_Shift& refCodeShift)
            : layerId(layerId), refLayerState(refLayerState),
              refCodeShift(refCodeShift) {}
        virtual void press();
        virtual void release();
};
#endif
