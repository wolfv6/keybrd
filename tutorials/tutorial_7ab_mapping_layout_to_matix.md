keybrd Tutorial 7ab - mapping layout to matrix
============================================
After reading this tutorial you will be able to map a keyboard layout to a keyboard matrix.

Keyboard mapping nomenclature
-----------------------------
**[Keyboard layout](http://en.wikipedia.org/wiki/Keyboard_layout)** - is the placement of keys.  Key caps are often labeled to show a keyboard's layout.

**[Matrix](http://pcbheaven.com/wikipages/How_Key_Matrices_Works/)** - is a collection of switches electrically connected into rows and columns.

**[Transpose](https://en.wikipedia.org/wiki/Transpose)** - is the mapping of layout rows to matrix columns.  Used when diodes are oriented with anodes towards the matrix rows.

When to use mapping
-------------------
In most of the other keybrd tutorial examples:
* layout and matrix are congruent
* active-low keyboard diodes are oriented with cathodes towards the matrix rows
  (or active-high keyboard diodes are oriented with anodes towards the matrix rows)

There is no standard way keyboards are manufactured.  Some variations are:
* irregular matrix
* active-low  keyboard diodes are oriented with anodes towards the matrix rows
* active-high keyboard diodes are oriented with cathodes towards the matrix rows
* I/O expander pins connect to matrix out of order

Any of these variations can use a mapping to align a layout with the matrix.

Mapping a layout to a matrix
----------------------------
Modify the basic breadboard keyboard by flipping diodes, so that anodes are towards matrix rows (blue bus).
The [keybrd_7a_mapping_single-layer.ino](keybrd_7a_mapping_single-layer/keybrd_7a_mapping_single-layer.ino) sketch will run on the keyboard.
Annotations in the sketch explain how mapping from LAYOUT to MATRIX works.

The [keybrd_7b_mapping_multi-layer.ino](keybrd_7b_mapping_multi-layer/keybrd_7b_mapping_multi-layer.ino) sketch will run on the same keyboard.

Exercise
--------
1) Make a keyboard with an irregular matrix.
 * Modify the basic breadboard keyboard by crossing the columns.
 * Modify the keybrd_2_single-layer.ino sketch by mapping the layout to the irregular matrix.

![crossed columns](keybrd_7_mapping_layout_to_matix/crossed_columns.jpg "crossed columns")

<br>
<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
