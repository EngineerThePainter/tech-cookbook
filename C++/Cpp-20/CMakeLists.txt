cmake_minimum_required(VERSION 3.12.0)
project(cpp20-features)

enable_testing()

set(CMAKE_CXX_STANDARD 20)
#Handle that it will be disabled for the google, as it spam errors
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if (UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif(UNIX)

set(SOURCES 
three_way_comparison.hpp
three_way_comparison.cpp
designated_initializer.hpp
designated_initializer.cpp
init_statement_initializer_ranged_for.hpp
init_statement_initializer_ranged_for.cpp
likely_unlikely.hpp
likely_unlikely.cpp
consteval_and_constinit.hpp
consteval_and_constinit.cpp
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCES})
