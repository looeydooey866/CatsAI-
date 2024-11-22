cmake_minimum_required(VERSION 3.14)
project(tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Ofast -march=native -funroll-loops")
set(SOURCE_FILES main.cpp
        board.cpp
        board.h
        data.h
        draw.cpp
        piece.cpp
        piece.h
        queue.cpp
        queue.h
        bench.cpp
        movegen.cpp
        movegen.h
)

add_executable(tetris ${SOURCE_FILES})
include_directories(/usr/local/include)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(tetris sfml-system sfml-window sfml-graphics sfml-audio sfml-network)