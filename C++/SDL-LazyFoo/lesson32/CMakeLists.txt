project(lesson32)

set(HEADERS 
include/lesson32/circle.hpp
include/lesson32/dot.hpp
include/lesson32/lesson32.hpp
include/lesson32/texture.hpp
include/lesson32/timer.hpp)

set(SOURCES
src/dot.cpp
src/lesson32.cpp
src/texture.cpp
src/timer.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::sdl CONAN_PKG::sdl_image CONAN_PKG::sdl_ttf)

target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_LIST_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)
