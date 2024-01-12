cmake_minimum_required(VERSION 3.20.0)
project(cpu)

add_executable(
  cpu
  src/main.cpp
  src/gate/gate.cpp
  src/adder/adder.cpp
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
add_subdirectory(googletest) # add googletest subdirectory
include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

# Function to create and link test executable
function(add_test_file TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} GTest::gtest_main)
endfunction()

add_test_file(example_test test/example_test.cpp)

include(GoogleTest)
gtest_discover_tests(example_test)

