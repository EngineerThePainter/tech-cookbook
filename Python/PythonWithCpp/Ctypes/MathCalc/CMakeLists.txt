cmake_minimum_required(VERSION 3.12.0)
project(MathCalc)

set(HEADERS math_calc.hpp)

set(SOURCES math_calc.cpp)

add_library(${PROJECT_NAME}
SHARED
${HEADERS}
${SOURCES}
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_11)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)
