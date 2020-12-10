project(common)

set(HEADERS
    include/common/common_prints.hpp
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
# target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra)
# if (UNIX)
#   target_compile_options(${PROJECT_NAME} INTERFACE -Wextra)
# endif(UNIX)