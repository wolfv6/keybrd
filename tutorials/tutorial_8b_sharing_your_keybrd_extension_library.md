Tutorial 8b - sharing your keybrd extension library
===================================================
Publishing and listing your keybrd extension library allows others to find and install your library.
The keybrd extension library name should start with "keybrd_" so that it is easy for other people to find.

There are two ways to publish and list an Arduino library.

Publish anywhere and list on Arduino Playground
-----------------------------------------------
Publishing your keybrd extension library with the following directory structure makes it easy for others to understand.

    keybrd_MyKeyboard/
        doc/
            keybrd_MyKeyboard_guide
        examples/
            keybrd_MyKeyboard1/
                keybrd_MyKeyboard1.ino
            keybrd_MyKeyboard2/
                keybrd_MyKeyboard2.ino
        class1.cpp
        class1.h
        class2.cpp
        class2.h
        ..
        instantiations_codes.h
        instantiations_rows.h

When your ready to list your keybrd extension library,
 add a link and short description of your keybrd extension library to the [Arduino Playground keybrd page](http://playground.arduino.cc/Main/keybrd) under "keybrd extension libraries".
Arduino playground is a wiki.
Links on how to edit the wiki are on the bottom left under "Participate".

Publish on GitHub and list on Arduino Library-Manager and Arduino Playground
----------------------------------------------------------------------------
The advantage of using GitHub is that users can submit pull requests.
The advantage of using Arduino Library-Manager is that users can easily find and install your library through the Arduino IDE.

Arduino Library-Manager is particular about the directory structures it accepts.
A library.properties file and a src folder need to be placed in your keybrd extension library like this:

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
            instantiations_rows.h

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
    url= (instert your MyKeyboard github repo URL here)
    architectures=*
```

Instructions for listing a library on Arduino Library Manager are at:
    https://github.com/arduino/Arduino/wiki/Library-Manager-FAQ

After it has been accepted into the Arduino IDE Library Manager,
 add a link and short description of your keybrd extension library to the [Arduino Playground keybrd page](http://playground.arduino.cc/Main/keybrd) under "keybrd extension libraries".
Arduino playground is a wiki.
Links on how to edit the wiki are on the bottom left under "Participate".

To publish a new release of a library that is already listed on Arduino Library Manager

1. Update the version in your library.properties file:

    version=0.5.0
    
2. Commit
3. Create an annotated tag with the version number:

    $ git tag -a v0.5.0 -m "version 0.5.0"

4. Push:

    $ git push -u --tags origin master

Arduino will eventually publish your new release.

<br>
<a rel="license" href="https://creativecommons.org/licenses/by/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://licensebuttons.net/l/by/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">keybrd tutorial</span> by <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd" property="cc:attributionName" rel="cc:attributionURL">Wolfram Volpi</a> is licensed under a <a rel="license" href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International License</a>.<br />Permissions beyond the scope of this license may be available at <a xmlns:cc="https://creativecommons.org/ns" href="https://github.com/wolfv6/keybrd/issues/new" rel="cc:morePermissions">https://github.com/wolfv6/keybrd/issues/new</a>.
