keybrd Tutorial 4 - Connecting split keyboards
===============================================
Split keyboards have left and right parts:
* one keyboard half contains the controller and USB port.
* the other keyboard half can contain shift registers or an I/O expander.

The two halves need to be connected.
The preferred connection method depends on the number of keys, number of available controller pins, cable flexibility, LEDs, and cost.

## Split keyboard connections table

| connection type        | controller pins | wire count | max keys |
|------------------------|:---------------:|:----------:|:--------:|
| just cable             | 3               | 6          |  9       |
| just cable             | 3               | 7          | 12       |
| just cable             | 4               | 8          | 16       |
| just cable             | 4               | 9          | 20       |
|                        |                 |            |          |
| 2 PISO shift registers | 3               | 5          | 16       |
| 3 PISO shift registers | 3               | 5          | 24       |
|                        |                 |            |          |
| I/O expander SPI       | 4               | 6          | 64       |
| I/O expander I2C       | 2               | 4          | 64       |

Fewer wires makes a cable more flexible.
A flexibility cable makes it easy to position the keyboard and route the cable.
But if there are enough pins on the controller, using just a cable with more wires is simpler and costs less.

I/O Expanders can power LEDs, while PISO shift registers can not.

I2C is a little slow if the I/O expander is scanning more than 4 rows.
The keybrd_DH (DodoHand) sketch polls 5 rows over I2C at 7.5ms per keyboard scan.
Which is acceptable, but faster would be nicer.

## Cables table

| connector name                                        | wire count |
|-------------------------------------------------------|:----------:|
| TRRS                                                  | 4          |
| 6-pin mini-DIN connector (PS/2)                       | 4          |
| USB 2                                                 | 4          |
| 4P4C Modular connector (RJ9, RJ10, RJ22) handset plug | 4          |
| 6P4C Modular connector (RJ-14) 2-line phone           | 4          |
| 6P6C Modular connector (RJ12) 3-line phone            | 6          |
| eSATA                                                 | 7          |
| 8p8c Modular connector (RJ45) Ethernet                | 8          |
| USB 3.0, 3.1                                          | 9          |

Only ready-made cables that are widely available are listed.
There are hundreds of other connectors listed at http://pinouts.ru/
There are also wireless options if you don't mind adding complexity and maintaining a battery.

The 8-wire "GearIT Cat 6 Ethernet Flat Patch Cable 7 Feet" is very flexible.
It's available at Walmart (9/19/16) if you want to feel the merchandise before you buy.
All the modular connectors are flat.

For prototyping on perfboards, consider a 0.1" header.

<br>
<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
