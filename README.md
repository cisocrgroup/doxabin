# δoxabin
Simple binariazation tool that uses the implemenataion of
[Δoxa](https://github.com/brandonmpetty/Doxa)'s implementation of
the ISauvola algorithm to binarize images.

## Usage
```
doxabin [Options] IN OUT
Options:
 -k n  set k-value (default 0.2)
 -w n  set window size (default 75)
```

## Compilation
To compile, first issue the following command:
`git submodule update --init --recursive`, then compile the
program with `make`.

## Installation
To install, first issue the following command:
`git submodule update --init --recursive`, then install the
program with `make install`.

## Dependencies
In order to compile the program the development headers for opencv4
must be installed on the system (libopencv-dev on Ubuntu).
Additionally, you need a c++ compiler and pkg-config installed on your
system.
