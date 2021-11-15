project(typeoverload)

set(HEADERS)

add_library(${PROJECT_NAME}
  INTERFACE
)

target_link_libraries(${PROJECT_NAME}
  INTERFACE
  traits
)

target_include_directories(${PROJECT_NAME}
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/include
)