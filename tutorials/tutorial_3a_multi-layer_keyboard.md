Tutorial 3a - multi-layer keyboard
==================================
When you finish this tutorial you will be able to be able to modify a multi-layer keybrd sketch to suite your own multi-layer keyboard design.

## Multi-layer nomenclature
**[layers](http://deskthority.net/wiki/Layer)** are key bindings provided by the keyboard firmware.  For example,
* The full-size [IBM PC keyboard](http://en.wikipedia.org/wiki/IBM_PC_keyboard) has one layer.
* Many compact keyboards have an additional [Fn layer](http://en.wikipedia.org/wiki/Fn_key).
* The [Neo layout](http://neo-layout.org/index_en.html) has 6 layers.

**layer code** - is an integer used to identify a layer.

**active layer** - is the layer currently used by the keyboard.

**layer scheme** - is a system for changing layers while typing (a single-layer scheme does not change layers).

## Pseudo code for simple layer scheme
The following pseudo code has just enough detail to show how layer schemes work.

**Layer** objects control the active layer.
There is one Key_Layer object for each layer.  Each Key_Layer object has a unique layer number.
When a Layer object is pressed, it tells StateLayer to change the active layer.
```
class Key_Layer
{
    int layer
    StateLayer& refState
    press() { refState.setLayer(layer) }
}
```

A **StateLayer** object's activeLayer is always up to date.
```
class StateLayer
{
    int activeLayer
    setActiveLayer(int layer) { activeLayer = layer }
    getActiveLayer() { return activeLayer }
}
```

**Layered** objects contain one scancode for each layer.
When a Layered object is pressed, it gets the active layer from StateLayer, and then presses the key of the active layer.
```
class Key_Layered
{
    Key** ptrsKeys          //array of Key pointers, one Key per layer
    StateLayer& refState
    press() { layer = refState.getLayer()
              ptrsKeys[layer]->press() }
}
```

## Layer-scheme classes
There are several layer scheme-classes to choose from.
You can view all the class definitions in the [keybrd library](../src/).

Layer classes include:
* Code_LayerHold
* Code_LayerLock

There is only one StateLayer class:
* StateLayer

Layered classes include:
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

(Future version of keybrd library may change all Code classes to Key classes.)

## A simple multi-layer keybrd sketch
The [keybrd_3a_multi-layer_annotated.ino](keybrd_3a_multi-layer_annotated/keybrd_3a_multi-layer_annotated.ino)
sketch uses three layer-scheme classes:
* StateLayers
* Code_LayerHold
* Key_LayeredKeysArray

Annotations in the sketch explain how the multi-layer feature works.

## Exercises
1) Modify the keybrd_3_multi-layer_annotated.ino sketch to use two Code_LayerLock objects.

| Layout | **0**  | **1**  |
|:------:|--------|--------|
|  **0** | a   1  | b   2  |
|  **1** | layer0 | layer1 |
