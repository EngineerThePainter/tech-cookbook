project(lesson30)

set(HEADERS 
include/lesson30/circle.hpp
include/lesson30/dot.hpp
include/lesson30/lesson30.hpp
include/lesson30/texture.hpp
include/lesson30/timer.hpp)

set(SOURCES
src/dot.cpp
src/lesson30.cpp
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
