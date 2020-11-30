cmake_minimum_required(VERSION 3.12.0)
project(Shapes)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC -Werror")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(HEADERS 
areas_calc.hpp
rectangle.hpp)

set(SOURCES
areas_calc.cpp
rectangle.cpp)

pybind11_add_module(${PROJECT_NAME} ${HEADERS} ${SOURCES} pybind_wrapper.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC)

add_executable(shapes main.cpp ${HEADERS} ${SOURCES})