cmake_minimum_required(VERSION 3.12.0)
project(tracy-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

option( TRACY_ENABLE "" ON)
option( TRACY_ON_DEMAND "" ON)
add_subdirectory (thirdparty/tracy)

add_executable(${PROJECT_NAME} main.cpp thirdparty/tracy/TracyClient.cpp)
target_link_libraries(${PROJECT_NAME} 
  PUBLIC 
  Tracy::TracyClient
)
