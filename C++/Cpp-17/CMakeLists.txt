cmake_minimum_required(VERSION 3.16.0)
project(cpp-17-features)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)

add_custom_command(TARGET cpp-17-features POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test_dir/ ${CMAKE_SOURCE_DIR}/build/bin/test_dir/)