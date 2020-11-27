#include <pybind11/pybind11.h>
#include "areas_calc.hpp"

void init_shapes(pybind11::module &);

PYBIND11_MODULE(pybind11_example, m) {
    init_shapes(m);
    m.doc() = "pybind11 example plugin"; // Optional module docstring
    m.def("rectangle_area_py", &rectangle_area, "Calculates rectangle area");
}