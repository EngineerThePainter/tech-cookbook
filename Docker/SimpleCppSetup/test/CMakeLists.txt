add_executable(docker-setup-unittest testDocker.cpp)

target_link_libraries(docker-setup-unittest
  PUBLIC
  CONAN_PKG::gtest
)

add_test(NAME docker-setup-unittest
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
  COMMAND docker-setup-unittest
)