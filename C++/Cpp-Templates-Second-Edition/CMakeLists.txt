cmake_minimum_required(VERSION 3.16.0)
project(cpp-templates-second-edition)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  basics
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)

add_subdirectory(basics)
