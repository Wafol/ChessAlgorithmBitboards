cmake_minimum_required(VERSION 3.26)
project(ChessAlgorithmBitboards)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChessAlgorithmBitboards main.cpp
        Board.cpp
        BoardUI.h
        BoardUI.cpp)
