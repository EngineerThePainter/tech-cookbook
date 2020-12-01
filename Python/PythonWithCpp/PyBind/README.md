# Pybind

### Table of Contents

1. [Description](#description)
2. [Installation](#installation)
3. [Files](#files)
4. [Licensing, Authors, and Acknowledgements](#licensing)

## Description <a name="description"></a>

The goal of this sub-project is to show basic capabilities of the Pybind C++ library.

## Installation <a name="installation"></a>

I was testing it only on Linux and invoke implementation aims to use bash.

First of all, download Python requirements:
```
pip install -r requirements.txt
```

This will download and install the `invoke` package - library that allows for making a terminal calls. The calls implementation is in the `tasks.py` file.

When you have invoke downloaded call the build task (when cd to this directory):
```
invoke build-pybind
```
This will:

* Create a `build` directory in the Shapes directory.
* Invoke conan install to download PyBind11 C++ library from conan repository.
* Build Shapes library using pybind wrapper.
* Copy library to this directory.

Then to see the usage of this module just run the `pybind_test.py` script:
```
python3 pybind_test.py
```

## Files <a name="files"></a>

* Shapes - the library used in this example.
* tasks.py - the python script required by `invoke` to run different system tasks.
* use_math_calc.py - python demo script.

## Licensing, Authors, and Acknowledgements <a name='licensing'></a>

As everything in this repo it's released under MIT License. When working on this sub-project I was using information from this [article](https://realpython.com/python-bindings-overview/) written by Jim Anderson and ctypes and pybind11 docs.

