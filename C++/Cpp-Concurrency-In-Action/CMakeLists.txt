cmake_minimum_required(VERSION 3.22)
project(cpp-concurrency)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)

add_executable(1.1 "chapter1/main.cpp")
add_executable(2.1 "chapter2/2_1.cpp")
add_executable(2.2 "chapter2/2_2.cpp")
add_executable(2.3 "chapter2/2_3.cpp")
add_executable(2.6 "chapter2/2_6.cpp")
add_executable(2.7 "chapter2/2_7.cpp")
add_executable(2.9 "chapter2/2_9.cpp")
add_executable(3.1 "chapter3/3_1.cpp")
add_executable(3.7_and_8 "chapter3/3_7_and_8.cpp")