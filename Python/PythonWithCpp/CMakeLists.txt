cmake_minimum_required(VERSION 3.12.0)
project(MathCalc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

set(HEADERS math_calc.hpp)

set(SOURCES math_calc.cpp)

add_library(${PROJECT_NAME}
SHARED
${HEADERS}
${SOURCES}
)

