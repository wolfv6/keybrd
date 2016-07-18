Tutorial 5 - indicator LEDs
===========================
Keyboards often have LEDs to indicate CapsLock, NumLock, and other states.
It's one of the first things we look at when a keyboard produces unexpected results.

Adding LEDs to the basic breadboard keyboard
--------------------------------------------
The breadboard keyboard modifies the basic breadboard keyboard described in [tutorial_1_breadboard_keyboard.md](tutorial_1_breadboard_keyboard.md)

Add components to the breadboard as shown in the picture.

The three clear plastic cylinders are LEDs.
LED anodes (the longer lead) are powered by 4.7k Ohm current limiting resistors connected to pins 16, 17, and 21.
LED cathodes (the shorter lead) are grounded by a common terminal strip.

!["LEDs"](keybrd_5_LEDs/LEDs_back.JPG "LEDs")

keybrd sketch for driving LEDs
------------------------------
[keybrd_5_LEDs.ino](keybrd_5_LEDs/keybrd_5_LEDs.ino) is a simple sketch with three LEDs.
The sketch will run on the above breadboard keyboard.
As usual, the sketch annotations explain the code.

LED brightness
--------------
An LED's current limiting resistor value effects the brightness of the LED.
Lets see how much visual difference resistance makes.
Replace an LED's 4.7k Ohm resistor with a 270 Ohm resistor.

It doesn't matter which end of the LED the resistor is on, the important thing is that the resistor and LED are in series.

Less resistance makes the LED brighter.
Too little resistance will burn out the LED.
Connecting an LED directly to power will destroy the LED in a bright flash (do not look directly at the LED if you try this).

2-mA LEDs are bright enough for keyboard indicator lights.
Or you can use more resistance on a 20-mA LED to make it dimmer.

LED current limiting resistor values
------------------------------------
Never connect an LED directly from ground to power.  Doing so would destroy the LED.

This formula calculates the minimum resistance for maximum LED brightness:
```
output-pin Supply Voltage   Vs
LED Forward Voltage         Vf
Forward Current             If

minimum current limiting restiance  R = (Vs - Vf) / If
```

For Forward Current, use the smaller of: 
* Current capacity of output pin
* Continuous Forward Current of LED

Teensy LC output-pin capacities are:
* four 20 mA pins (5, 16, 17, 21)
* nineteen 5 mA pins
* Teensy LC on-board LED is on pin 13.
  It has a current-limiting resistor on the board, and does not provide enough power for another LED.

For Teensy LC 20 mA pin and the TT Electronics OVLLx8C7 LED:
```
output-pin Supply Voltage   Vs = 3.3 volts
LED Forward Voltage         Vf = 2.2 volts
max pin Current             If = 20 mA
max LED Current             If = 20 mA

minimum current limiting restiance  R = (Vs - Vf) / If = 55 Ohms
```
It is safe to use more resistance.

Calculating the resistance for the Teensy LC 5 mA pin is left as an exercise.

Through-the-hole resistors have color coded bands that indicate resistance value.
 https://en.wikipedia.org/wiki/Electronic_color_code#Resistor_color-coding

Exercises
---------
1) In this exercise you will calculate the minimum current limiting resistance needed for your output pin and LED.

For your micro controller, find:
* Supply Voltage coming out of the output pins
* Current (mA) capacity of the output pins

From your LED's  datasheet, find:
* Forward Voltage
* Continuous Forward Current (mA)

Calculate the minimum resistance needed for your LED and Supply Voltage.
There are several "LED current limiting resistor calculators" on line.

<br>
<a rel="license" href="http://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="http://creativecommons.org/ns#" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
