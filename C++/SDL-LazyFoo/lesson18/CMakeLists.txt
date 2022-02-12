project(lesson18)

set(HEADERS 
include/lesson18/button.hpp
include/lesson18/lesson18.hpp
include/lesson18/texture.hpp)

set(SOURCES
src/button.cpp
src/lesson18.cpp
src/texture.cpp)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::sdl CONAN_PKG::sdl_image)

target_include_directories(${PROJECT_NAME}
PUBLIC
${CMAKE_CURRENT_LIST_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)
