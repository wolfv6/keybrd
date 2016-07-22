Tutorial 10 - writing your own port classes
===========================================
Port classes are the keybrd library's interface to I/O expander ports.

To write your own port classes:

1. Get a copy of the controller or I/O expander datasheet.
2. Study other keybrd Port classes.

For example, the keybrd_DH library use these keybrd classes for its PCA9655E I/O:
* PortWrite_PCA9655E
* PortRead_PCA9655E
* LED_PCA9655E

Debugging I/O expander code is hard because SPI or I2C protocol adds a level of indirection.
If you haven't written Arduino code for an I/O expander before, learn from an Arduiono I/O expander tutorial before attempting it here.

<br>
<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
