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

include(GoogleTest)

# Function to create and link test executable
function(add_test_file TEST_NAME TEST_FILES)
    add_executable(${TEST_NAME} test/${TEST_NAME}.cpp ${TEST_FILES})
    target_link_libraries(${TEST_NAME} GTest::gtest_main)
    gtest_discover_tests(${TEST_NAME})
endfunction()

add_executable(
  adder_test test/adder_test.cpp src/gate/gate.cpp src/adder/adder.cpp
)
target_link_libraries(adder_test GTest::gtest_main)
gtest_discover_tests(adder_test)
