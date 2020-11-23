project(basics)

set(HEADERS
    include/chapter1.hpp
    include/chapter2.hpp
    include/chapter3.hpp
    include/common_prints.hpp
    include/basics/max.hpp
    include/basics/max_return_type.hpp
    include/basics/max_overloads.hpp
    include/basics/stack1.hpp
    include/basics/stack2.hpp
    include/basics/stack3.hpp
    include/basics/stackpartspec.hpp
    include/basics/stacknontype.hpp
    include/basics/stackTemplateParameterAuto.hpp
    include/basics/templatized_aggregate.hpp
)

set(SOURCES
    src/chapter1.cpp
    src/chapter2.cpp
    src/chapter3.cpp
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