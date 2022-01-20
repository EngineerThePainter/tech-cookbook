cmake_minimum_required(VERSION 3.19)

project(sdl-lazyfoo)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(HEADERS
  lesson1/lesson1.hpp
  lesson2/lesson2.hpp
  lesson3/lesson3.hpp
  lesson4/lesson4.hpp
  lesson5/lesson5.hpp
  lesson6/lesson6.hpp
  lesson7/lesson7.hpp
  lesson8/lesson8.hpp
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
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

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
  lesson8)

add_custom_command(TARGET sdl-lazyfoo POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/images/ ${CMAKE_SOURCE_DIR}/build/bin/images/)