#ifndef CHESSALGORITHMBITBOARDS_CHESSENUMS_H
#define CHESSALGORITHMBITBOARDS_CHESSENUMS_H

#pragma once

//UPPERCASE=WHITE, lowercase=black
typedef enum PieceType {
    P=0, R=1, N=2, B=3, Q=4, K=5, p=6, r=7, n=8, b=9, q=10, k=11, NONE
} PieceType;

typedef enum CastlingType {
    CASTLE_WK = 0, CASTLE_WQ = 1, CASTLE_BK = 2, CASTLE_BQ = 3
} CastlingType;

#endif //CHESSALGORITHMBITBOARDS_CHESSENUMS_H
