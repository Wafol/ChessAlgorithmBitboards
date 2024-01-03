cmake_minimum_required(VERSION 3.26)
project(ChessAlgorithmBitboards)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChessAlgorithmBitboards main.cpp
        ChessBoard/Board.cpp
        ChessBoard/BoardUI.h
        ChessBoard/BoardUI.cpp
        ChessBoard/MovesGeneration.cpp
        ChessBoard/OneMove.h
        ChessBoard/OneMove.cpp
        ChessBoard/ChessEnums.h
)
