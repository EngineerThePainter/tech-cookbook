cmake_minimum_required(VERSION 3.12.0)
project(learn-opengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(HEADERS
hello_triangle.hpp
hello_triangle_two_triangles.hpp
hello_triangle_two_triangles_different_buffers.hpp
hello_triangle_two_triangles_different_shaders.hpp
)

set(SOURCES
hello_triangle.cpp
hello_triangle_two_triangles.cpp
hello_triangle_two_triangles_different_buffers.cpp
hello_triangle_two_triangles_different_shaders.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
PUBLIC
${CONAN_TARGETS}
)
