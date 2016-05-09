Tutorial 8 - breaking up a sketch into smaller files
====================================================
A keybrd sketch can become quite lengthy, which can make it harder to navigate and understand.

The keybrd_DH sketch has about 800 lines of code; 700 of which are for instantiating objects.
The object instantiations are grouped into four files located in the keybrd_DH library, and included in keybrd_DH.ino:

    // ========= OBJECT INSTANTIATIONS =============
    #include <instantiations_ports.h>
    #include <instantiations_LEDs.h>
    #include <instantiations_codes.h>
    #include <instantiations_matrix.h>

Splitting your code into groups of instantiations also provides organizational and reusability benefits.

Example 1.
You have three versions of LED indicators you are experimenting with:
    instantiations_LEDs_1.h
    instantiations_LEDs_2.h
    instantiations_LEDs_3.h

Example 2.
You use Colemak and want QWERTY users to to try your keyboard design.
So you publish your keybrd extension library with two versions of instantiations_matrix.h:
    instantiations_matrix_QWERTY.h
    instantiations_matrix_colemak.h

Example 3.
Someone wants to try the layout in your keybrd extension library, but their controller and matrix are different.
So they replace two of your object instantiation files with their own:
    instantiations_ports.h
    instantiations_matrix.h
