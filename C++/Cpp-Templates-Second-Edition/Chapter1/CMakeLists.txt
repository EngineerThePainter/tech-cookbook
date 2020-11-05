cmake_minimum_required(VERSION 3.16.0)
project(cpp-templates-chapter1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

set(HEADERS basics/max.hpp)
set(HEADERS basics/max_return_type.hpp)

add_executable(${PROJECT_NAME} main.cpp ${HEADERS})

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  basics)
