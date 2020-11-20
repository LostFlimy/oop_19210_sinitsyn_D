cmake_minimum_required(VERSION 3.17)
project(lab3_Warships)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab3_Warships main.cpp cell.cpp cell.h ship.cpp ship.h interface.h interface.cpp)