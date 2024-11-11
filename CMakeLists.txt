cmake_minimum_required(VERSION 3.14)
project(tetris)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops -fopt-info-vec-optimized")

set(SOURCE_FILES main.cpp
                 piece.cpp
                 board.cpp
                 queue.cpp
                 piece.h
                 queue.h
                 board.h
                 point.h
        draw.cpp
        data.h)

add_executable(tetris ${SOURCE_FILES})

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(tetris sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
