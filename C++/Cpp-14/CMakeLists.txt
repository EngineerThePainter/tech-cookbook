cmake_minimum_required(VERSION 3.16.0)
project(cpp-14-features)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_14)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)