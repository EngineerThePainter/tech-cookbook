enable_testing()

add_executable(
  simple-test
  simpleTest.cpp
)

target_link_libraries(
  simple-test
  gtest_main
)

add_test(NAME simple-test
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND simple-test
)

# Instead of going with enable_testing() and add_test you can go with CMake built-in commands:
# # Adds possibility to use a Google Test Infrastructure
# include(GoogleTest)
# # Automatically adds ctest by querying the list of provided binaries
# gtest_discover_tests(simple-test)