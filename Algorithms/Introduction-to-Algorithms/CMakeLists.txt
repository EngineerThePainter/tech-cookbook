cmake_minimum_required(VERSION 3.16.0)
project(introduction-to-algorithms)

set(HEADERS
sorting_algorithm.hpp
chapter2/chapter2.hpp
chapter2/insertion_sort.hpp
utils/time_tracker.hpp
)

set(SOURCES
sorting_algorithm.cpp
chapter2/src/chapter2.cpp
chapter2/src/insertion_sort.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)

target_include_directories(${PROJECT_NAME} 
  PUBLIC
  chapter2
  utils)