# Change Log for keybrd library
All notable changes to the keybrd project will be documented in this file.
This project adheres to [Semantic Versioning 2.0.0](http://semver.org/).

keybrd version 0.x.x is for initial development. The public API should not be considered stable.
keybrd version 1.0.0 will be released when the public API is stable.

## [Unreleased]

## [0.3.2] - 2016-06-21
### Added
config_keybrd.h for size configurations.
RowScanner_SPI-ShiftRegisters for compact split keyboards up to 32 keys per matrix.
LED_PinNumber for controlling indicator lights by pin number.

## [0.3.2] - 2016-06-10
### Changed
* Changed uC from scanning port arrays to scanning Arduino pins, thereby adding support for:
    Arduino boards, Teensy 3, and Teensy LC micro controllers
    up to 31x31 matrix capability
* Changed IOE from scanning port arrays to scanning single ports.
* Moved scanner and debouncer into their own classes.

### Added
* Row_uC
* Row_IOE
* RowScannerInterface
* RowScanner_PinsArray
* RowScanner_PinsBitwise
* DebouncerInterface
* Debouncer_4Samples

### Removed
* Port arrays

## [0.3.1] - 2016-06-02
### Added
* RowBase class
* Row::debounce()

## [0.3.0] - 2016-05-09
### Changed
* Restructured the project directory to conform to Arduino library manager specifications
    * Moved keybrd_DH library extension (for DodoHand) to its own repository
    * Moved sketches to examples directory
* Replaced Key_Layered dependency on LayerManager with LayerState class

### Added
* Tutorials

## [0.2.0] - 2016-02-25
### Added
* Port classes for micro-controllers and I/O expanders
* DH_2565 sketch with DataHand layout
* Sticky mouse button (SMB) for DataHand layout
* Supporting documentation

## [0.1.0] - 2015-02-10
### Added
* The library runs on Teensy 2.0 microcontroller and MCP23018 I/O expander
* Limited to 8x8 matrix, which is enough for compact or split keyboards
* First draft of supporting documentation
* Example keybrd sketches for single-layer, multi-layer, and DataHand layer schemes

