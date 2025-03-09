# iota

iota is a small programming language.

It implements the operations from klong, which is a dialect of APL in the k family.

# The iota-cpp Project

The iota-cpp project is an implementation of the iota programming language in C++ that is portable across
Arduino-compatible microcontrollers and Linux-compatible microprocessors. It contains both a cross-platform core and
platform-specific extensions for Arduino and Linux.

## Dependencies:
- cmake, ninja
- arduino-cli (for iota-arduino and iota-arduino-protocol-server)
- A c++ compiler on your host system (for iota-stdio)
- If you want to test it on an Arduino, you need an Adafruit RP2350 Feather with HSTX at the moment.

The whole project and all build targets are built from the top-level project using cmake, using the usual invocation:
```aiignore
mkdir build
cd build
cmake ..
make
```

## The iota-cpp Library

The core of the iota-cpp project is the iota-cpp library. This both compiles as a static library for Linux and can be
imported as an Arduino library.

A core principle of iota is that it is portable. It is agnostic to platform-specific differences such as processor type,
machine word size, and endianness. It does require a compiler compatible with the C++17 standard, which is unfortunately
not available for all Arduino cores. Modern cores such as the RP2040/RP2350 and Teensy 4.0/4.1 support C++17.

## The iota-stdio Executable

The goal of iota-stdio is to give you a simple interface for Linux where you can pipe iota programs into this executable
and pipe the results of the computation back out. Right now, this is just an empty template for the code that will be
written later. The purpose it serves is to have a Linux target to compile against in order to ensure that the iota-cpp
libraries compiles on Linux.

## The iota-arduino Library

The iota-arduino library adds Arduino-specific functionality on top of iota-cpp. This code should be cross-platform to
any Arduino cores that support the C++17 standard. Right now, the main functionality this adds is serial input and
output. However, in the future this is where things like GPIO, I2C, and SPI interfaces will be added.

### The iota-arduino-protocol-server Example

Inside iota-arduino/examples is the iota-arduino-protocol-server program. If you run this on your Arduino, it will set
it up to read serialized iota programs through the Arduino's serial port, evaluate the programs, and write a serialized
version of the result of the computation back out of the serial port. This allows for a debugging feature that I call
"drive-by-wire". You can write programs on one machine (say your Linux computer) and then run them on an Arduino. This
is very handy for testing code and trying out different features of the language. There is a separate repository, sip
(Serial iota for Python), that has a full suite of unit tests, all written in python, that you can run on your Arduino
using iota-arduino-protocol-server and drive-by-wire.

## Features
- Beautiful code, written meticulously and with love in my heart
- Cross-platform between microcontrollers (Arduino) and microprocessors (Linux)
- Builds for all supported platforms, including cross-compiling, on your host machine with one build process (cmake)
- Contains no Rust code, has never been "entirely rewritten in Rust" as is the trend these days (this might be an anti-feature for some)
- Easily extensible to add new nouns and verbs