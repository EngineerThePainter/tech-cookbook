project(cpp-with-libraries)
cmake_minimum_required(VERSION 3.20)
#TODO make atomic works
set(Boost_COMPILER clangw12)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.77.0 COMPONENTS chrono)


message("Boost Found: " ${Boost_FOUND})
message("Boost Include Dirs: " ${Boost_INCLUDE_DIRS})
message("Boost Library Dirs: " ${Boost_LIBRARY_DIRS})
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

#TODO dynamic boost
#TODO pure cmake calls
# cmake . -G Ninja -B .\build\
# cmake --build .\build\