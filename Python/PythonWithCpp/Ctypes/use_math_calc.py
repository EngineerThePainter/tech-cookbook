import ctypes
import pathlib

def main():
    libname = pathlib.Path().absolute() / "libMathCalc.so"
    print(libname)
    math_calc_cpp = None
    try:
        math_calc_cpp = ctypes.CDLL(libname)
    except OSError:
        print("Unable to load the system C++ library")
        sys.exit()

    math_calc_cpp.add.restype = ctypes.c_double
    x = 5.5
    y = 12.23
    answer = math_calc_cpp.add(ctypes.c_double(x), ctypes.c_double(y))
    print(f"Adding using C++ shared library of x:{x}, y:{y} gives us: {answer}")

if __name__ == "__main__":
    main()