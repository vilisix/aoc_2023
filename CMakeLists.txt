cmake_minimum_required(VERSION 3.27)
project(aoc_2023)

set(CMAKE_CXX_STANDARD 17)

add_executable(aoc_2023 main.cpp
        aoc1/aoc1.h
        aoc2/aoc2.h
        aoc3/aoc3.h
        aoc4/aoc4.h
        aoc5/aoc5.h)
