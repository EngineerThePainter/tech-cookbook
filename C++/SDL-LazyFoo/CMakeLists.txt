cmake_minimum_required(VERSION 3.19)

project(sdl-lazyfoo)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(HEADERS
  lesson1/lesson1.hpp
  lesson2/lesson2.hpp
  lesson3/lesson3.hpp
  lesson4/lesson4.hpp
  lesson5/lesson5.hpp
  lesson6/lesson6.hpp
  lesson7/lesson7.hpp
  lesson8/lesson8.hpp
  lesson9/lesson9.hpp
  lesson10/lesson10.hpp
  lesson10/texture.hpp
)

set(SOURCES
  lesson1/src/lesson1.cpp
  lesson2/src/lesson2.cpp
  lesson3/src/lesson3.cpp
  lesson4/src/lesson4.cpp
  lesson5/src/lesson5.cpp
  lesson6/src/lesson6.cpp
  lesson7/src/lesson7.cpp
  lesson8/src/lesson8.cpp
  lesson9/src/lesson9.cpp
  lesson10/src/lesson10.cpp
  lesson10/src/texture.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} 
  CONAN_PKG::sdl
  CONAN_PKG::sdl_image
  CONAN_PKG::sdl_ttf
  lesson11
  lesson12
  lesson13
  lesson14
  lesson15
  lesson16
  lesson17
  lesson18
  lesson19
  lesson20
  lesson22
  lesson23
  lesson24
  lesson25
  lesson26
  lesson27
  lesson28
  lesson29
  lesson30
  lesson31)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)

target_include_directories(
  ${PROJECT_NAME} 
  PUBLIC 
  lesson1
  lesson2
  lesson3
  lesson4
  lesson5
  lesson6
  lesson7
  lesson8
  lesson9
  lesson10)

add_subdirectory(lesson11)
add_subdirectory(lesson12)
add_subdirectory(lesson13)
add_subdirectory(lesson14)
add_subdirectory(lesson15)
add_subdirectory(lesson16)
add_subdirectory(lesson17)
add_subdirectory(lesson18)
add_subdirectory(lesson19)
add_subdirectory(lesson20)
add_subdirectory(lesson22)
add_subdirectory(lesson23)
add_subdirectory(lesson24)
add_subdirectory(lesson25)
add_subdirectory(lesson26)
add_subdirectory(lesson27)
add_subdirectory(lesson28)
add_subdirectory(lesson29)
add_subdirectory(lesson30)
add_subdirectory(lesson31)

add_custom_command(TARGET sdl-lazyfoo POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/images/ ${CMAKE_BINARY_DIR}/bin/images/)

add_custom_command(TARGET sdl-lazyfoo POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/sounds/ ${CMAKE_BINARY_DIR}/bin/sounds/)