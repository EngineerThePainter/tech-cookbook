# Use C++ libraries with CMake only

The goal of this small project is to present ways how to link external libraries into your C++ project. I am going to keep this README more like a tutorial/notebook with all useful information that I gained, since I'm doing it on Windows where it's not so straightforward. Another reason is that I wanted to learn better how CMake works, and oh boy - on Windows it was a ride.

## Ways of having an external library into your C++ project.

Based on my experience I know two ways how to handle this situation when using a CMake. We can get a built library into our system (like Boost or PyTorch) or we can add it as a CMake component into our project like (GoogleTest).

### Add pre-build library

Some libraries (like Boost or PyTorch) are meant to be compiled on their own so they can be used in multiple projects at once. PyTorch for Windows is delivered in a built form directly.

To include the library you need to know where it is in your filesystem and then, by the `find_package()` function in CMake include it into your project. Keep in mind this will give information to CMake where to find library headers and compiled sources - you will need to link the library using `target_link_libraries` as well.

Keep in mind that CMake also needs to know where to find such a package, then the CMAKE_PREFIX_PATH variable needs to be set (either by setting explicitely in a way: `-DCMAKE_PREFIX_PATH="(path_to_boost);"`. I set it in my VS Code settings for convinience.

### Add library as a git submodule

First, start with adding a git submodule that will point to the git repository (if you wish you can just download it as well, but this way you can easily change the version if required).

`git submodule add` 'link to library' for example: 'git@github.com:google/googletest.git'

Then just from the directory just go and go to the branch/tag with the desired release.

Then you can just add include it to be built as a part of your project - see `CMakeLists.txt` in the root directory.

You can run tests using `ctest` from the build directory.


## How to build it

* Be sure you have a [CMake](https://cmake.org/) in version at least 3.20.
* You have to get and install Boost in your system, windows [example]
(https://www.boost.org/doc/libs/1_55_0/more/getting_started/windows.html).
* Install [CUDA](https://developer.nvidia.com/cuda-downloads) and [CUDNN](https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html) in your system.
* Get [PyTorch](https://pytorch.org/get-started/locally/) library in C++ with CUDA support for your CUDA version. The CUDA version MUST MATCH EXACTLY to your PyTorch!
* I am using VS Code on Windows with plugins for CMake and CMake Tools (don't confuse with Visual Studio) and MSVC compiler (before adding PyTorch with CUDA to this project I was using clang, but I had too many issues with CUDA and by looking into PyTorch cmakefiles definition it seemed to me like the default compiler for this library is MSVC - at least I had an impression).

## Lessons learned from this sub-project

* When doing it on Windows it is better for your mind health if you use a MSVC compiler.
* Visual Studio Code CMake offers a good approach to configure CMake and C++ features. My `settings.json` for this sub-project looks like follows:
```
{
  "C_Cpp.default.cppStandard": "c++17",
  "C_Cpp.default.cStandard": "c11",
  "C_Cpp.default.includePath": ["${workspaceFolder}/**", "path_to_boost/**", "path_to_pytorch/**", "path_to_msvc_include/**"],
  "C_Cpp.autocomplete": "Default",
  "C_Cpp.default.intelliSenseMode": "windows-msvc-x64",
  "C_Cpp.errorSquiggles": "Disabled",
  "C_Cpp.default.compilerPath": "path_to_msvc_compiler.exe",
  "cmake.configureEnvironment": {
    "CMAKE_PREFIX_PATH": "path_to_boost;path_to_pytorch"
  },
  "cmake.configureSettings": {
    "Boost_COMPILER": "clangw12",
    "Boost_USE_STATIC_LIBS": "ON",
    "Boost_USE_STATIC_RUNTIME": "OFF"
  }
}
```