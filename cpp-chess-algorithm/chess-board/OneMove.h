#ifndef CHESSALGORITHMBITBOARDS_ONEMOVE_H
#define CHESSALGORITHMBITBOARDS_ONEMOVE_H


#include <cstdint>
#include <string>
#include "ChessEnums.h"

class OneMove {
public:
    //oznacuje jestli je pohyb platny nebo ne (tzn. jestli ho pouzivat nebo ne)
    bool valid = true;

    uint8_t i1; //start i
    uint8_t j1; //start j
    uint8_t i2; //end i
    uint8_t j2; //end j

    PieceType promotion = NONE; //pawn promotion on rank 8

    OneMove();
    OneMove(uint8_t i1, uint8_t j1, uint8_t i2, uint8_t j2): i1(i1), j1(j1), i2(i2), j2(j2) {}
    OneMove(uint8_t i1, uint8_t j1, uint8_t i2, uint8_t j2, PieceType promotion): i1(i1), j1(j1), i2(i2), j2(j2), promotion(promotion) {}

    std::string toString() const;
private:
};


#endif //CHESSALGORITHMBITBOARDS_ONEMOVE_H
