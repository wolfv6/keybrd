Tutorial 3cde - sublayer keyboard
=================================
This tutorial assumes the reader understands the previous tutorial.

When you finish this tutorial you will be able to be able to modify a multi-layer keybrd sketch to write your very own multi-layer keyboard firmware.

Sublayer nomenclature
---------------------
**primary layer** - is a layer whose layer key is accessible from the default layer.

**sublayer** - is a layer whose layer key is not accessible from the default layer.

**layer group** - is a group of layers that occupy the same keys.

Layer scheme with a sublayer
----------------------------
This tutorial has 3 example sketches, all using this layout:

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Num |
|  **1** |Normal | Sym   | Enter |

Each cell in the table's body represents a key.
Bottom row keys have one layer.
Top row keys have 2 or 3 layers.

Pressing the "Normal" layer key locks the Normal layer.
Letters 'a' 'b' 'c' are on the Normal layer.

Pressing the "Sym" layer key locks the Sym layer.
Symbols '-' '=' are on the Sym layer.

The "Num" sublayer key is on the Sym layer.
If the keyboard is locked on the Sym layer, holding Num down makes Num the active layer.
Releasing the Num key restores the Sym layer.
Number '1' is on the Num sublayer.

todo [pic of 3 col bb kb]

Three example 3 sketches implement the above layout using differently layer schemes.
Keybrd provides flexibility todo??
Which layer scheme is best depends on the layout.

3c - 
-----------
keybrd_3c_sublayerNull.ino

The layer scheme has one LayerState object cover all the layer groups.
Duplicate codes and null codes fill the unused space.
It's a bit of a kludge, but can be simple if there is little unused space.

3d - 
-----------
keybrd_3d_sublayerNestedKeys.ino

The layer scheme has a distinct LayerState object for each layer group.
One LayerState object per layer group is preferred because it models the logic of the layout.

In this example, NORMAL+SYM is the primary layer group, which covers the top-row keys.
layerState keeps track of the primary layer group's active layer.

SUBSYM+SUBNUM is the sublayer group, which covers the top-left key.
subLayerState keeps track of the sublayer group's active layer.

The concepts of "sublayer" and "layer group" are independent.
In the following layout for example, l_num and s_enter codes have swapped places.
Num is now a primary layer, and SYM2+NUM2 is still layer group2.

| Layout | **0** | **1** | **2** |
|:------:|:-----:|:-----:|:-----:|
|  **0** | a - 1 | b =   | c Ent |
|  **1** |Normal | Sym   |  Num  |

3e - 
-----------
keybrd_3e_sublayerNestedScSc.ino

Key_LayeredKeys constructor takes any number of code arguments.
Key_LayeredScSc is more specialized.  It's constructor takes exactly two scancode arguments.
No array was created for the two scancodes.
This has advantages when a large sublayer group has two layers:
* save SRAM
* less clutter in sketch

with custom layer classes, any layer scheme can be implemented
DH is a complex layer scheme implemented with keybrd lib

Complex layerschemes
--------------------
The basic LayerState class used in the tutorials is sufficient for implementing many layer schemes.
More complicated layer schemes would need custom LayerState classes, and possibly custom Code_Layer and Key_Layered classes as well.

keybrd_DH is an example of a complex layer scheme (it emulates the DataHand keyboard).
It's the most complex layer scheme I know of.
The keybrd_DH project is a showcase of the keybrd library's capability.
Don't let the complexity scare you; most layer schemes are much simpler.

keybrd_DH's layout has 3 layers and 5 sub-layers.
Most of the layer classes are custom classes, which reside in the keybrd_DH library.
Layer classes used by keybrd_DH are listed below.
The length of the list gives a hint of the layer scheme's complexity.

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

