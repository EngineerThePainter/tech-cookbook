cmake_minimum_required(VERSION 3.16.0)
project(introduction-to-algorithms)

set(HEADERS
divide-and-conquer/maximum_subarray.hpp
matrix/matrix_multiply.hpp
searching/binary_search.hpp
sorting/bubble_sort.hpp
sorting/demo_sorting.hpp
sorting/insertion_sort.hpp
sorting/merge_sort.hpp
sorting/merge_sort_improved.hpp
sorting/sorting_algorithm.hpp
utils/time_tracker.hpp
)

set(SOURCES
divide-and-conquer/src/maximum_subarray.cpp
matrix/src/matrix_multiply.cpp
searching/src/binary_search.cpp
sorting/src/bubble_sort.cpp
sorting/src/demo_sorting.cpp
sorting/src/insertion_sort.cpp
sorting/src/merge_sort.cpp
sorting/src/merge_sort_improved.cpp
sorting/src/sorting_algorithm.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
# if (UNIX)
#   target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
# endif(UNIX)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -fsanitizer=memory)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -fsanitizer=memory)


target_include_directories(${PROJECT_NAME} 
  PUBLIC
  divide-and-conquer
  matrix
  searching
  sorting
  utils)