project(basics)

set(HEADERS
    include/chapter1.hpp
    include/chapter2.hpp
    include/common_prints.hpp
    include/basics/stack1.hpp
    include/basics/max.hpp
    include/basics/max_return_type.hpp
    include/basics/max_overloads.hpp
)

set(SOURCES
    src/chapter1.cpp
    src/chapter2.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)