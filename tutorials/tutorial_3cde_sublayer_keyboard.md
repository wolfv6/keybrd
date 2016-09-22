Tutorial 3cde - sublayer keyboard
=================================
This tutorial assumes the reader understands the previous tutorial.

When you finish this tutorial you will be able to be able to modify a multi-layer keybrd sketch to write your very own multi-layer keyboard firmware.

Sublayer nomenclature
---------------------
These definitions are specific to the keybrd library.

**layer group** - is a group of layers that occupy the same keys.

**primary layer group** - is a layer group containing the default layer.

**sublayer group** - is a layer group nested in a layer of another layer group.

**primary layer** - is a layer within the primary layer group.

**sublayer** - is a layer within the sublayer group.

Layer scheme with a sublayer
----------------------------
This tutorial has 3 example sketches, all using this layout:

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Num |
|  **1** | Alpha |  Sym  | Enter |

Each cell in the table's body represents a key.
Bottom row keys have one layer.
Top row keys have 2 or 3 layers.

Pressing the "Alpha" layer key locks the Alpha layer.
Letters 'a' 'b' 'c' are on the Alpha layer.

Pressing the "Sym" layer key locks the Sym layer.
Symbols '-' '=' and "Num" layer key are on the Sym layer.

If the keyboard is locked on the Sym layer, holding Num down makes Num the active layer.
Releasing the Num key restores the Sym layer.
Number '1' is on the Num sublayer.

todo [pic of 3 col bb kb]

Three example sketches implement the above layout using differently layer schemes.
Which layer scheme is best depends on the layout.

Sketch 3c - one layer group
---------------------------
Refer to keybrd_3c_sublayerNull.ino

The top row has one layer group with 3 layers.
Num layer is unused to the right of 1.
Duplicate codes and null codes fill the unused space.
It's a bit of a kludge, but can be simple if there is little unused space.

layerState contains the active layer for the layer group.

Sketch 3d - two layer groups
----------------------------
Refer to keybrd_3d_sublayerNestedKeys.ino

The top row has two layer groups.
* NORMAL+SYM is the primary layer group.  It covers the top-row keys.
* SYM1+NUM1 is a sublayer group nested in the SYM layer.  The subgroup covers the top-left key.

Two layer groups model the logic of the layout accurately
(the previous example was a kluge because it only had one layer group).

There should be one LayerState object for each layer group.  In this example:
* layerState contains the active layer for the primary layer group.
* sublayerState contains the active layer for the sublayer group.

Sketch 3e - specialized layered keys
------------------------------------
Refer to keybrd_3e_sublayerNestedScSc.ino

Key_LayeredKeys constructor takes any number of code or key arguments.
Key_LayeredScSc is more specialized.  It's constructor takes exactly two scancode arguments.
A Key_LayeredScSc object could be instantiated with Key_LayeredKeysArray.
But using Key_LayeredScSc has advantages when a large sublayer group has two layers:
* no array is created for the two scancodes
* less clutter in sketch
* save SRAM

Key_Layered classes include:
* Key_LayeredKeys   (any number of codes or keys)
* Key_LayeredScSc   (specialized for two scancodes)
* Key_LayeredCodeSc (specialized for one code and one scancode)

Sublayer layer-key placement
----------------------------
A layer key to a sublayer can be place in one of two places:
* on layer the sublayer group is nested in (layout above has Num-layer key on Sym layer)
* on a single-layer key (layout below has Num-layer key on bottom row) (some people would not call this arrangement a sublayer)

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Ent |
|  **1** | Alpha |  Sym  |  Num  |

Complex layerschemes
--------------------
The basic LayerState class used in the tutorials is sufficient for implementing many layer schemes.
More complicated layer schemes would need custom LayerState classes, and possibly custom Code_Layer and Key_Layered classes as well.
Any layer scheme can be implemented with the right custom layer classes.

[keybrd_DH](https://github.com/wolfv6/keybrd_DH) is an example of a complex layer scheme (it emulates the DataHand keyboard).
The keybrd_DH sketch is a showcase of the keybrd library's capability.
It's the most complex layer scheme I know of.
Don't let the complexity scare you; most layer schemes are much simpler.

Layer-scheme classes used by keybrd_DH are listed below.
The layer scheme classes are organized into three categories, as is "Layer-scheme classes" in the previous tutorial.
Most of the layer-scheme classes are custom classes, which reside in the keybrd_DH library.

DH Code_Layer classes include:
* Code_LayerLock
* Code_LayerLockMF_Protector
* Code_LayerState_Toggle

DH LayerState classes include:
* LayerState
* LayerState_DH
* LayerState_NAS

DH Key_Layered classes include:
* Key_LayeredKeys
* Key_LayeredScSc
* Key_LayeredNav
* Key_LayeredDoublePressToggle 
* Key_LayeredCodeSc_MF
* Key_LayeredOperator
* Key_LayeredNumber
* Key_LayeredNumber_00

Exercises
---------
Modify keybrd_3e_sublayerNestedScSc.ino by adding the number '2' to the Num layer group.
The layout is below.

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b = 2 | c Num |
|  **1** | Alpha |  Sym  | Enter |
