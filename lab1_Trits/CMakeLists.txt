cmake_minimum_required(VERSION 3.17)
project(lab1_Trits)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../googletest build)

include_directories(../googletest/include)

add_executable(lab1_Trits main.cpp class_Trit.h class_Trit_Set.h class_Trit_Set.cpp class_Trit.cpp tests.cpp)

target_link_libraries(lab1_Trits gtest gtest_main)