project(common)

set(HEADERS
    include/common/common_prints.hpp
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)
