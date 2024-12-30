cmake_minimum_required(VERSION 3.22)

project(ai-for-games)

set(CMAKE_CXX_STANDARD 23)

if (UNIX)
    set(VCPKG_TARGET_TRIPLET "x64-linux")
endif()

set(VCPKG_ROOT "${CMAKE_CURRENT_LIST_DIR}/thirdparty/vcpkg" CACHE STRING "Path to Vcpkg root directory")
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}")

option(ENABLE_SANITIZERS "Enable sanitizers" OFF)
if(ENABLE_SANITIZERS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize=undefined")
endif()

find_package(Allegro CONFIG REQUIRED)
find_package(loguru CONFIG REQUIRED)

set(HEADERS 
"allegro.hpp"
"algorithm_runner.hpp"
"kinematic/arrive.hpp"
"kinematic/seek.hpp"
"kinematic/wander.hpp"
"kinematic/kinematic_common.hpp"
"kinematic/kinematic_data.hpp"
)

set(SOURCES 
"allegro.cpp"
"kinematic/arrive.cpp"
"kinematic/seek.cpp"
"kinematic/wander.cpp"
"kinematic/kinematic_common.cpp"
"kinematic/kinematic_data.cpp"
)

add_executable(ai-for-games main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC
Allegro::allegro_main
Allegro::allegro_primitives
Allegro::allegro_image
Allegro::allegro_font
loguru
)
