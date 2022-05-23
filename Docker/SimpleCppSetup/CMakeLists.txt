cmake_minimum_required(VERSION 3.12.0)

project(docker-setup-cpp)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(test)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)