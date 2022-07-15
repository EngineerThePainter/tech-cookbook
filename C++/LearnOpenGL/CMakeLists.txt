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
shaders.hpp
shaders_triangle_upside_down.hpp
shaders_horizontal_offset.hpp
shaders_color_as_position.hpp
textures.hpp
textures_face_reversed.hpp
textures_experiments.hpp
textures_centric.hpp
textures_visibility_manipulation.hpp
transformations.hpp
transformations_second_container.hpp
coordinates.hpp
coordinates_container_rotating.hpp
camera.hpp
)

set(SOURCES
hello_triangle.cpp
hello_triangle_two_triangles.cpp
hello_triangle_two_triangles_different_buffers.cpp
hello_triangle_two_triangles_different_shaders.cpp
shaders.cpp
shaders_triangle_upside_down.cpp
shaders_horizontal_offset.cpp
shaders_color_as_position.cpp
textures.cpp
textures_face_reversed.cpp
textures_experiments.cpp
textures_centric.cpp
textures_visibility_manipulation.cpp
transformations.cpp
transformations_second_container.cpp
coordinates.cpp
coordinates_container_rotating.cpp
camera.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${HEADERS} ${SOURCES} thirdparty/stb_image.h)

target_link_libraries(${PROJECT_NAME}
PUBLIC
${CONAN_TARGETS}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/images/ ${CMAKE_BINARY_DIR}/bin/images/)