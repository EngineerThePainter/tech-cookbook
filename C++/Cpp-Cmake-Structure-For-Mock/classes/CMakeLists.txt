project(classes)

set(HEADERS
include/classes/animal.hpp
include/classes/user.hpp
include/classes/user_actions.hpp
)

set(SOURCES
src/animal.cpp
src/user_actions.cpp
)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME}
PUBLIC
include
PRIVATE
src
)

add_subdirectory(test)