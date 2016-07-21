Tutorial 8b - creating and publishing your own keybrd extension library
=======================================================================
Publishing and listing your keybrd extension library allows others to find and install your library.
The keybrd extension library name should start with "keybrd_" so that it is easy for people to find.

The directory structure of the library depends on where it will be listed.

Publishing anywhere with listing on Arduino Playground LibraryList
------------------------------------------------------------------
Arduino Playground LibraryList can list a library with any directory structure.
The directory structure of your keybrd extension library can be as simple as:

    keybrd_MyKeyboard/
        class1.cpp
        class1.h
        class2.cpp
        class2.h
        ..
        instantiations_codes.h
        instantiations_ports.h
        instantiations_matrix.h
        doc/
            keybrd_MyKeyboard_guide
        examples/
            keybrd_MyKeyboard1/
                keybrd_MyKeyboard1.ino
            keybrd_MyKeyboard2/
                keybrd_MyKeyboard2.ino

[Arduino playground](http://playground.arduino.cc/) is a wiki.
Instructions for listing a library on the Arduino playgound LibraryList are at:
    http://playground.arduino.cc/Code/Library#Sharing

Add your keybrd library to the Keyboard/Keypads sublist:
    http://playground.arduino.cc/Main/InterfacingWithHardware#keyb

Publishing on GitHub with listing on Arduino Library-Manager and Arduino Playground LibraryList
-----------------------------------------------------------------------------------------------
The advantage of using GitHub is that users can submit pull requests.
The advantage of using Arduino Library-Manager is that users can install your library through the Arduino IDE.

Arduino Library-Manager is particular about the directory structures it accepts.
Your keybrd extension library should have a library.properties file and a src folder, placed like this:

    keybrd_MyKeyboard/
        library.properties
        doc/
            keybrd_MyKeyboard_guide
        examples/
            keybrd_MyKeyboard1/
                keybrd_MyKeyboard1.ino
            keybrd_MyKeyboard2/
                keybrd_MyKeyboard2.ino
        src/
            class1.cpp
            class1.h
            class2.cpp
            class2.h
            ..
            instantiations_codes.h
            instantiations_ports.h
            instantiations_matrix.h

The library.properties file is described in
    https://github.com/arduino/Arduino/wiki/Arduino-IDE-1.5:-Library-specification

Example library.properties file:
```
    name=keybrd_MyKeyboard
    version=1.2.3
    author=Me
    maintainer=Me
    sentence=An extension to the keybrd library for the MyKeyboard.
    paragraph=This library demonstrates my feature.
    category=Device Control
    url= (github repo URL for keybrd_MyKeyboard)
    architectures=*
```

Instructions for listing a library on Arduino Library Manager are at:
    https://github.com/arduino/Arduino/wiki/Library-Manager-FAQ

[Arduino playground](http://playground.arduino.cc/) is a wiki.
After it has been accepted into the Arduino IDE Library Manager, add your library to the Arduino Playground LibraryList.
Sign in at http://playground.arduino.cc/Main/LibraryList and add keybrd libraries to Keyboard/Keypads sublist:
    http://playground.arduino.cc/Main/InterfacingWithHardware#keyb

<br>
<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
