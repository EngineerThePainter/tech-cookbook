cmake_minimum_required(VERSION 3.16.0)
project(introduction-to-algorithms)

set(HEADERS
data-structures/bst.hpp
data-structures/linked_list.hpp
data-structures/queue.hpp
data-structures/rb_tree.hpp
data-structures/stack.hpp
dynamic-programming/cut_rod.hpp
dynamic-programming/longest_common_subsequence.hpp
divide-and-conquer/maximum_subarray.hpp
heap/heap.hpp
matrix/matrix_multiply.hpp
searching/binary_search.hpp
sorting/bubble_sort.hpp
sorting/counting_sort.hpp
sorting/demo_sorting.hpp
sorting/heap_sort.hpp
sorting/insertion_sort.hpp
sorting/merge_sort.hpp
sorting/merge_sort_improved.hpp
sorting/quicksort.hpp
sorting/randomized_quicksort.hpp
sorting/sorting_algorithm.hpp
utils/time_tracker.hpp
)

set(SOURCES
data-structures/src/bst.cpp
data-structures/src/linked_list.cpp
data-structures/src/queue.cpp
data-structures/src/rb_tree.cpp
data-structures/src/stack.cpp
dynamic-programming/src/cut_rod.cpp
dynamic-programming/src/longest_common_subsequence.cpp
divide-and-conquer/src/maximum_subarray.cpp
matrix/src/matrix_multiply.cpp
searching/src/binary_search.cpp
sorting/src/bubble_sort.cpp
sorting/src/counting_sort.cpp
sorting/src/demo_sorting.cpp
sorting/src/heap_sort.cpp
sorting/src/insertion_sort.cpp
sorting/src/merge_sort.cpp
sorting/src/merge_sort_improved.cpp
sorting/src/quicksort.cpp
sorting/src/randomized_quicksort.cpp
sorting/src/sorting_algorithm.cpp)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES} main.cpp)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)


target_include_directories(${PROJECT_NAME} 
  PUBLIC
  data-structures
  divide-and-conquer
  dynamic-programming
  heap
  matrix
  searching
  sorting
  utils)