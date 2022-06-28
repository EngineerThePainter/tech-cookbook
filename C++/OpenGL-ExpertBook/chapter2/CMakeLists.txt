project(chapter2)

set(HEADERS
chapter2.hpp
)

set(SOURCES
chapter2.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
PUBLIC
CONAN_PKG::sdl
CONAN_PKG::glew
CONAN_PKG::glu
)

target_include_directories(${PROJECT_NAME}
PUBLIC
# ${CMAKE_CURRENT_LIST_DIR}/include
${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall)
if (UNIX)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wextra)
endif(UNIX)