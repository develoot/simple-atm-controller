# Simple ATM Controller

A simple ATM Controller implementation for coding test.

Classes which depend on external components (e.g., Bank API or ATM Hardware) are also implemented
but not functioning because no external components are actually implemented. So it's natural to
fail all tests for them.

This implementation is written in Ubuntu 20.04 environment. I recommend you to use it as it ships
with CMake 3.16 and Qt 5.12.

## Dependencies

 - CMake >= 3.16
 - Qt >= 5.12

## How to build

In the project root directory,

```
$ cmake -B <output_directory> . && cmake --build build -j $(nproc)
```

Substitute `<output_directory>` with wherever you want.

## How to test

In the output directory,

```
$ ctest -j $(nproc)
```
