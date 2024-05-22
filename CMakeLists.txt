# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Название проекта
project(FacadePattern)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавить исходные файлы
add_executable(Iterator Iterator.cpp)

# Добавить тесты
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(Iterator1 tests/test.cpp)
target_link_libraries(Iterator1 ${GTEST_LIBRARIES} pthread)

add_test(NAME Iterator1 COMMAND Iterator1)
