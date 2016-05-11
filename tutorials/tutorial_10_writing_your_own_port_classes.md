Tutorial 8 - writing your own port classes
==========================================
Port classes are the keybrd library's interface to microcontoller ports and I/O expander ports.

To write your own port classes:
 1) Get a copy of the controller or I/O expander datasheet.
 2) Study keybrd port classes that use a similar IC.
 3) Consider looking for other open-source keyboard code that uses the same IC e.g. TMK keyboard firmware.
 4) Write your RowPort_* class to inherit from RowPort class.
 5) Write your ColPort_* class to inherit from ColPort class.

Writing port classes is the most technically demanding task in the keybrd library.
It might be faster to designing your keyboard around one of the controllers or I/O expanders that already have port classes in the keybrd library.

<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
