# SDL by Lazy Foo

This is a tutorial project to learn about the SDL library. The work is done based on the tutorial from [LazyFoo](https://lazyfoo.net/tutorials/SDL/index.php).

# Why there is a strange SDL directory, while I'm using conan?

In the beginning I was not using conan here. This file contains some trick for Windows when using this library (it was not compiled with the project, it contained headers and static libraries) - the build required this cmake configuration file for SDL in order to compile correctly.

## Licensing

The code here base on the lessons from the [LazyFoo](https://lazyfoo.net/tutorials/SDL/index.php) - however it's not copy-pasting the original codes, but rather 
re-implementation of their lessons.
