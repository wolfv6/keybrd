Tutorial 8 - writing your own port classes
==========================================
Port classes are the keybrd library's interface to microcontoller ports or I/O expander ports.

To write your own port classes:
 1) Get a copy of the controller or I/O expander datasheet.
 2) Study keybrd port classes that use a similar IC.
 3) Consider looking for other open-source keyboard code that uses the same IC e.g. TMK keyboard firmware.
 4) Write your RowPort_* class to inherit from RowPort class.
 5) Write your ColPort_* class to inherit from ColPort class.
 6) Consider testing on a breadboard keyboard.

Writing port classes is the most technically demanding task in the keybrd library.
If you have not read a controller datasheet or I/O expander datasheet before,
 consider designing your keyboard around one of the controllers or I/O expanders
 that already have port classes in the keybrd library.

