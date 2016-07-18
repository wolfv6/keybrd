Tutorial 9 - breaking up a sketch into smaller files
====================================================
A keybrd sketch can become quite lengthy, which can make it harder to navigate and understand.

The keybrd_DH sketch has about 800 lines of code; 700 of which are for instantiating objects.
The object instantiations are grouped into six files located in the keybrd_DH library, and included in keybrd_DH.ino:

    // ========= INSTANTIATE THE KEYBOARD ==========
    #include "config.h"
    #include <instantiations_pins.h>
    #include <instantiations_scancodes.h>
    #include <instantiations_layercodes.h>
    #include <instantiations_rows_L.h>
    #include <instantiations_rows_R.h>

Splitting your code into groups of instantiations also provides organizational and reusability benefits.

Example 1.
You have three versions of LED indicators you are experimenting with:
* instantiations_LEDs_1.h
* instantiations_LEDs_2.h
* instantiations_LEDs_3.h

Example 2.
You use Colemak and want QWERTY users to to try your new keyboard design.
So you publish your keybrd extension library with two versions of instantiations_matrix.h:
* instantiations_matrix_colemak.h
* instantiations_matrix_QWERTY.h

<br>
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
