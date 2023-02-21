cmake_minimum_required(VERSION 3.0)

project(cmake-object-libraries)

add_subdirectory(a)
add_subdirectory(b)

add_executable(${PROJECT_NAME} main.cpp a.hpp b.hpp $<TARGET_OBJECTS:objectA> $<TARGET_OBJECTS:objectB>)