cmake_minimum_required(VERSION 3.16.0)
project(cpp-templates-second-edition)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  chapters
)

target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)

add_subdirectory(basics)
add_subdirectory(bridge)
add_subdirectory(chapters)
add_subdirectory(common)
add_subdirectory(details)
add_subdirectory(inherit)
add_subdirectory(poly)
add_subdirectory(traits)
add_subdirectory(typelist)
add_subdirectory(typeoverload)
add_subdirectory(tuples)
add_subdirectory(variant)
