#include <pybind11/pybind11.h>
#include "areas_calc.hpp"

PYBIND11_MODULE(Shapes, m) {
    m.doc() = "pybind11 example plugin"; // Optional module docstring
    m.def("rectangle_area_py", &rectangle_area, "Calculates rectangle area");
}