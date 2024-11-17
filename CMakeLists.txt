cmake_minimum_required(VERSION 3.14)
project(tetris)

#PLEASE USE O3/OFAST PLEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEASE
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Ofast -march=native -funroll-loops")
set(SOURCE_FILES main.cpp board.cpp board.h data.h draw.cpp
piece.cpp piece.h queue.cpp queue.h
        bench.cpp
)

add_executable(tetris ${SOURCE_FILES})
include_directories(/usr/local/include)