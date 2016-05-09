Tutorial 3a - multi-layer keyboard
==================================
After reading this tutorial you will be able to be able to modify a multi-layer keybrd sketch to suite your own multi-layer keyboard design.

## Multi-layer nomenclature
**[layers](http://deskthority.net/wiki/Layer)** are key bindings provided by the keyboard firmware.  For example,
* The full-size [IBM PC keyboard](http://en.wikipedia.org/wiki/IBM_PC_keyboard) has one layer.
* Many compact keyboards have an additional [Fn layer](http://en.wikipedia.org/wiki/Fn_key).
* The [Neo layout](http://neo-layout.org/index_en.html) has 6 layers.

**layer code** - is an integer used to identify a layer.

**active layer** - is the layer currently used by the keyboard.

**layer scheme** - is a system for changing layers while typing (a single-layer scheme does not change layers).

## A simple multi-layer keybrd sketch
This annotated sketch demonstrates the multi-layer feature:
[keybrd_3_multi-layer_annotated.ino](keybrd_proj/keybrd/examples/tutorials/keybrd_3_multi-layer_annotated/keybrd_3_multi-layer_annotated.ino)

## Layer scheme classes
The walkthrough example covered the most basic classes.
This section takes a general view of layer scheme classes.
You can view all the class definitions in the [keybrd library](keybrd/src/).

### StateLayer
StateLayer object has an active layer.  StateLayer keeps its active layer up to date.
There is only one StateLayer class:
* StateLayer

### Layer
Layer objects control the active layer.  For example, there could be one layer key for each layer.
When a Layer object is pressed, it tells StateLayer to change the active layer.
Example Layer classes include:
* Code_LayerHold
* Code_LayerLock

### Multi-layered
Layered objects contain one scancode for each layer.
When a Layered object is pressed, it gets the active layer from StateLayer, and then sends the scancode of the active layer.
Example Layered classes include:
* Code_LayeredScSc
* Code_LayeredCodeSc
* Code_LayeredCodeCode
* Key_LayeredKeysArray

## Single-layer Codes
Most Code objects only have one scancode or one layer code.
They do are not affected by the active layer.
Example single-layer Code classes include:
* Code_Sc
* Code_ScS
* Code_ScNS
* Code_Shift
* Code_LayerHold
* Code_LayerLock

(Future version of keybrd library may change all Code classes to Key classes.)

## Exercises
1) Modify the keybrd_3_multi-layer_annotated.ino sketch to use two Code_LayerLock objects.

| Layout | **0**  | **1**  |
|:------:|--------|--------|
|  **0** | a   1  | b   2  |
|  **1** | layer0 | layer1 |
