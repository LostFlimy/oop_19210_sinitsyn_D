cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(../googletest build)

include_directories(../googletest/include)

add_executable(lab4 main.cpp PrintTuple.h csvParser.cpp csvParser.h)
target_link_libraries(lab4 gtest gtest_main)