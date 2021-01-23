project(basics)

# set(HEADERS
#     # include/basics/max.hpp
#     # include/basics/max_return_type.hpp
#     # include/basics/max_overloads.hpp
#     # include/basics/stack1.hpp
#     # include/basics/stack2.hpp
#     # include/basics/stack3.hpp
#     # include/basics/stackpartspec.hpp
#     # include/basics/stacknontype.hpp
#     # include/basics/stackTemplateParameterAuto.hpp
#     # include/basics/templatized_aggregate.hpp
#     # include/basics/varprint1.hpp
# )

add_library(${PROJECT_NAME}
    INTERFACE
    # ${HEADERS}
)

target_link_libraries(${PROJECT_NAME}
    INTERFACE
    common
)

target_include_directories(${PROJECT_NAME}
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
# if (UNIX)
#   target_compile_options(${PROJECT_NAME} PRIVATE -Wextra)
# endif(UNIX)
