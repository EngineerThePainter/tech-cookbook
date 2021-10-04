cmake_minimum_required(VERSION 3.20)

project(cpp-with-libraries)

set(CMAKE_CXX_STANDARD 11)

set(Boost_COMPILER clangw12)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.77.0 COMPONENTS chrono)

message("Boost Found: " ${Boost_FOUND})
message("Boost Include Dirs: " ${Boost_INCLUDE_DIRS})
message("Boost Library Dirs: " ${Boost_LIBRARY_DIRS})

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

add_subdirectory(googletest)
add_subdirectory(test)
#TODO dynamic boost

#TODO pure cmake calls
# cmake . -G Ninja -B .\build\
# cmake --build .\build\

#TODO README where all information will be provided

#TODO Add gtest as a thirdparty library with cmake

#TODO Add Pytorch and run build with CUDA