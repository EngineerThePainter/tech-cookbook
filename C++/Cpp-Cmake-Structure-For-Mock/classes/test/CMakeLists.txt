project(classes_test)

find_package(GTest REQUIRED)

set(SOURCES
animal_mock.hpp
animal_test.cpp
user_actions_mock.hpp
user_test.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
PUBLIC
GTest::gtest_main
GTest::gmock
classes
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
