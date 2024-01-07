#ifndef CHESSALGORITHMBITBOARDS_CHESSENUMS_H
#define CHESSALGORITHMBITBOARDS_CHESSENUMS_H

#pragma once

//UPPERCASE=WHITE, lowercase=black
typedef enum PieceType {
    P=0, R=1, N=2, B=3, Q=4, K=5, p=6, r=7, n=8, b=9, q=10, k=11, NONE=12
} PieceType;

typedef enum CastlingType {
    CASTLE_WK = 0, CASTLE_WQ = 1, CASTLE_BK = 2, CASTLE_BQ = 3
} CastlingType;

typedef enum PlayerType {
    WHITE = 0, BLACK = 1, BOTH = 2
} PlayerType;

typedef enum GameOver {
    WHITE_WINS, BLACK_WINS, DRAW, NOT_OVER
} GameOver;

#endif //CHESSALGORITHMBITBOARDS_CHESSENUMS_H
