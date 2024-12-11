# Xmake

Xmake is a cross build tool for C++ that has a potential to be better than alternatives like cmake, vcpkg, conan etc.
It allows to build and execute everything from a single file instead of creating multiple files like in conan where you must both create both a CMakeLists.txt and conanfile.py.

This repo should act as a reminder for me how to do stuff in Xmake.

# What I'm going to show here

I want to present a simple C++ program that utilizes the following three libraries:

* Boost
* Allegro5
* Imgui

Additionally this project will contain separate library that will be linked to the main.cpp.

# How to proceed

* Create a `xmake.lua` file - see the repo content
    * Call `xmake` - to build
    * Call `xmake run` - to run
    * Call `xmake run -d <target-name>` to run debugger
    * Other super-useful stuff can be found [here](https://github.com/xmake-io/xmake) on the official Xmake site.

* Install VCPKG and set the $VCPKG_ROOT variable