# Place loguru.hpp and loguru.cpp in the same directory as your CMakeLists.txt
project(loguru)

add_library(loguru STATIC loguru.hpp loguru.cpp)

target_include_directories(loguru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})