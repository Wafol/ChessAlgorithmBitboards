//
// Created by pavel on 16.12.2023.
//

#ifndef CHESSALGORITHMBITBOARDS_ONEMOVE_H
#define CHESSALGORITHMBITBOARDS_ONEMOVE_H


#include <cstdint>
#include "Board.h"

class OneMove {
public:
    uint8_t i1;
    uint8_t j1;
    uint8_t i2;
    uint8_t j2;

    Board::PieceType promotion = Board::NONE; //pawn promotion on rank 8

    OneMove();
    OneMove(uint8_t i1, uint8_t j1, uint8_t i2, uint8_t j2): i1(i1), j1(j1), i2(i2), j2(j2) {}
private:
};


#endif //CHESSALGORITHMBITBOARDS_ONEMOVE_H
