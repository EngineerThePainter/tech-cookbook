project(classes)

set(HEADERS
include/classes/animal.hpp
)

set(SOURCES
src/animal.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME}
PUBLIC
include
PRIVATE
src
)

add_subdirectory(test)