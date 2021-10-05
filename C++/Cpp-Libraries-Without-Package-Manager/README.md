# Use C++ libraries with CMake only

The goal of this small project is to present ways how to link external libraries into your C++ project.

## Add pre-build library

Some libraries (like Boost or PyTorch) are meant to be compiled on their own so they can be used in multiple projects at once. PyTorch for Windows is delivered in a built form directly.

To include the library you need to know where it is in your filesystem and then, by the `find_package()` function in CMake include it into your project. Keep in mind this will give information to CMake where to find library headers and compiled sources - you will need to link the library using `target_link_libraries` as well.

Keep in mind that CMake also needs to know where to find such a package, then the CMAKE_PREFIX_PATH variable needs to be set.

My CMake call command looks like following (Windows and using Ninja):

```cmake . -G Ninja -B .\build\ -DCMAKE_PREFIX_PATH=(path_to_boost);(path_to_another_package)...```

## Add library as a git submodule

First, start with adding a git submodule that will point to the git repository (if you wish you can just download it as well, but this way you can easily change the version if required).

`git submodule add` 'link to library' for example: 'git@github.com:google/googletest.git'

Then just from the directory just go and go to the branch/tag with the desired release.

Then you can just add include it to be built as a part of your project - see `CMakeLists.txt` in the root directory.

You can run tests using `ctest` from the build directory.
