Tutorial 3a - multi-layer keyboard
==================================
When you finish this tutorial you will be able to be able to modify a multi-layer keybrd sketch to suite your own multi-layer keyboard design.

## Multi-layer nomenclature
**[layers](http://deskthority.net/wiki/Layer)** are key bindings provided by the keyboard firmware.  For example,
* The classic [IBM PC keyboard](http://en.wikipedia.org/wiki/IBM_PC_keyboard) has one layer.
* Many compact keyboards have an additional [Fn layer](http://en.wikipedia.org/wiki/Fn_key).
* The [Neo layout](http://neo-layout.org/index_en.html) has 6 layers.

**layer id** - is an integer used to identify a layer.

**active layer** - is the layer currently used by the keyboard.

**layer scheme** - is a system for changing layers while typing (a single-layer scheme does not change layers).

## Pseudo code for simple layer scheme
The following pseudo code has just enough detail to show how layer schemes work.

**Key_Layer** objects are used to select an active layer.
The "layer" variable is a layer id number.
When a Key_Layer object is pressed, it tells LayerState to update the active layer.
```
class Key_Layer
{
    int layer
    LayerState& refLayerState
    press() { refLayerState.setActiveLayer(layer) }
}
```

**LayerState** objects keep track of the active layer.
A LayerState's activeLayer is always up to date.
```
class LayerState
{
    int activeLayer
    setActiveLayer(int layer) { activeLayer = layer }
    getActiveLayer() { return activeLayer }
}
```

**Key_Layered** objects contain multiple elements, one element for each layer.
Layer ids are used like indexes to send the appropriate element.
When a Key_Layered object is pressed, it gets the active layer from LayerState, and then sends the appropriate element.
```
class Key_Layered
{
    Key** ptrsKeys          //array of Key pointers, one Key pointer per layer
    LayerState& refLayerState
    press() { layer = refLayerState.getActiveLayer()
              ptrsKeys[layer]->press() }
}
```

Dependency diagram
```
     +-----------+
     | Key_Layer |
     +-----------+
          |
          |setActiveLayer()
          |
          v
    +------------+
    | LayerState |
    +------------+
          ^
          |
          |getActiveLayer()
          |
    +-------------+
    | Key_Layered |
    +-------------+
```
## Layer-scheme classes
There are several layer scheme-classes to choose from.
You can view all the class definitions in the [keybrd library](../src/).

Key_Layer classes include:
* Code_LayerHold
* Code_LayerLock

A basic LayerState class is:
* LayerState

Key_Layered classes include:
* Code_LayeredScSc
* Code_LayeredCodeSc
* Code_LayeredCodeCode
* Key_LayeredKeysArray

## Single-layer Codes
Most Code objects only have one scancode or code.
They are not affected by the active layer.
Example single-layer Code classes include:
* Code_Sc
* Code_ScS
* Code_ScNS
* Code_Shift
* Code_LayerHold
* Code_LayerLock

<!-- todo -->

(Future version of keybrd library may change all Code classes to Key classes.)

## A simple multi-layer keybrd sketch
The [keybrd_3a_multi-layer_annotated.ino](keybrd_3a_multi-layer_annotated/keybrd_3a_multi-layer_annotated.ino)
sketch uses three layer-scheme classes:
* LayerState
* Code_LayerHold
* Key_LayeredKeysArray

Annotations in the sketch explain how the multi-layer feature works.

## Exercises
1) Modify the keybrd_3_multi-layer_annotated.ino sketch to use two Code_LayerLock objects.

| Layout | **0**  | **1**  |
|:------:|--------|--------|
|  **0** | a   1  | b   2  |
|  **1** | layer0 | layer1 |

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
