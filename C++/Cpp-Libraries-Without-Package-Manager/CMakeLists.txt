cmake_minimum_required(VERSION 3.20)

project(cpp-with-libraries)

# By finding Boost CMake sets a bunch of the useful variables
find_package(Boost 1.77.0 COMPONENTS chrono)
message("Boost Found: " ${Boost_FOUND})
message("Boost Include Dirs: " ${Boost_INCLUDE_DIRS})
message("Boost Library Dirs: " ${Boost_LIBRARY_DIRS})

find_package(Torch REQUIRED)

enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${TORCH_LIBRARIES})
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall)

# From Torch documentation:
# The following code block is suggested to be used on Windows.
# According to https://github.com/pytorch/pytorch/issues/25457,
# the DLLs need to be copied to avoid memory errors.
#
# I built it without it in the first place, but it happened that by some 
# reason these DLL's were not visible during the runtime. 
# Looks like a shortcut for me to not dive into real issue.
if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET cpp-with-libraries
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:cpp-with-libraries>)
endif (MSVC)

add_subdirectory(googletest)
add_subdirectory(test)
