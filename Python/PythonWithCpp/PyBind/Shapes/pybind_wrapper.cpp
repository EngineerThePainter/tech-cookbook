#include <pybind11/pybind11.h>
// This need to be included just for automatic conversion for shapes::getRectangles()
#include <pybind11/stl.h>

#include "areas_calc.hpp"
#include "rectangle.hpp"

namespace py = pybind11;

PYBIND11_MODULE(Shapes, m) {
    m.doc() = "pybind11 example plugin"; // Optional module docstring
    m.def("rectangle_area_py", &rectangle_area, "Calculates rectangle area");

    py::class_<shapes::Rectangle>(m, "Rectangle")
    .def(py::init<const double, const double, const double, const double>())
    .def("set_x", &shapes::Rectangle::setX)
    .def("set_y", &shapes::Rectangle::setY)
    .def("set_width", &shapes::Rectangle::setWidth)
    .def("set_height", &shapes::Rectangle::setHeight)
    .def("get_x", &shapes::Rectangle::getX)
    .def("get_y", &shapes::Rectangle::getY)
    .def("get_width", &shapes::Rectangle::getWidth)
    .def("get_height", &shapes::Rectangle::getHeight);

    m.def("get_rectangles", &shapes::getRectangles);
}