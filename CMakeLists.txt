cmake_minimum_required(VERSION 3.10)
project(Iterator)
set(CMAKE_CXX_STANDARD 14)     
add_executable(Iterator Iterator.cpp)
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Iterator1 tests/test.cpp)
target_link_libraries(Iterator1 ${GTEST_LIBRARIES} pthread)

add_test(NAME Iterator1 COMMAND Iterator1)
