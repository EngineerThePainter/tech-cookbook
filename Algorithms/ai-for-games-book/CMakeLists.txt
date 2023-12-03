cmake_minimum_required (VERSION 3.8)

project(ai-for-games)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS 
"allegro.hpp"
"algorithm_runner.hpp")

set(SOURCES 
"allegro.cpp"
"kinematic/seek.cpp")

add_executable(ai-for-games main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
allegro
allegro_primitives
allegro_image
loguru
)

add_subdirectory(thirdparty)

