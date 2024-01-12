This code uses [opencm3](https://github.com/libopencm3/libopencm3) library to wrap some hardware specific code.

In order to build it first you must build the opencv3 itself - just go with `make` for it.

Then see the `Makefile` - there is a couple of variables there - they are required by the `rules.mk` provided by the opencm3.

When the code is built (adapt the port and pin to your device), just go with 
```
st-flash write <binary-file> 0x8000000
```
This will flash your CPU (double check if writable part of your flash starts at 0x8000000).
