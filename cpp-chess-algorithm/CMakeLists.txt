cmake_minimum_required(VERSION 3.26)
project(ChessAlgorithmBitboards)

set(CMAKE_CXX_STANDARD 17)

add_executable(ChessAlgorithmBitboards main.cpp
        chess-board/Board.cpp
        chess-board/BoardUI.h
        chess-board/BoardUI.cpp
        chess-board/MovesGeneration.cpp
        chess-board/OneMove.h
        chess-board/OneMove.cpp
        chess-board/ChessEnums.h
        ChessEngine.cpp
        ChessEngine.h
)
