cmake_minimum_required (VERSION 3.8)

project(ai-for-games)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS 
"allegro.hpp"
"algorithm_runner.hpp"
"kinematic/arrive.hpp"
"kinematic/seek.hpp"
"kinematic/kinematic_data.hpp"
)

set(SOURCES 
"allegro.cpp"
"kinematic/arrive.cpp"
"kinematic/seek.cpp"
"kinematic/kinematic_data.cpp"
)

add_executable(ai-for-games main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
allegro
allegro_primitives
allegro_image
allegro_font
loguru
)

add_subdirectory(thirdparty)
