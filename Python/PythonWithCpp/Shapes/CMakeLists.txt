cmake_minimum_required(VERSION 3.12.0)
project(Shapes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Werror")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

pybind11_add_module(Shapes areas_calc.cpp areas_calc.hpp pybind_wrapper.cpp)
target_link_libraries(Shapes PUBLIC)

add_executable(shapes main.cpp areas_calc.cpp areas_calc.hpp)