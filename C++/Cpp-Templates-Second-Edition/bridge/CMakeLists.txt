project(bridge)

set(HEADERS)

add_library(${PROJECT_NAME}
  INTERFACE
)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
)

target_include_directories(${PROJECT_NAME}
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/include
)