cmake_minimum_required(VERSION 3.17)
project(lab0_WordCounter)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../googletest build)

include_directories(../googletest/include)

add_executable(lab0_WordCounter main.cpp lineReader.cpp lineReader.h tokenService.cpp tokenService.h wordStateService.cpp wordStateService.h reportService.cpp reportService.h)

target_link_libraries(lab0_WordCounter gtest gtest_main)