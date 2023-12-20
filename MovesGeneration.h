#ifndef CHESSALGORITHMBITBOARDS_MOVESGENERATION_H
#define CHESSALGORITHMBITBOARDS_MOVESGENERATION_H


#include <cstdint>
#include <vector>
#include "Board.h"
#include "OneMove.h"

class MovesGeneration {
public:
    std::vector<OneMove> generatePieceMoves(uint64_t (&bitboards)[12], Board::PieceType p_type);

private:
    uint64_t rank_masks[8] = { 0xFF00000000000000ULL, 0xFF000000000000ULL, 0xFF0000000000ULL, 0xFF00000000ULL, 0xFF000000ULL, 0xFF0000ULL, 0xFF00ULL, 0xFFULL };
    uint64_t file_masks[8] { 0x101010101010101ULL, 0x202020202020202ULL, 0x404040404040404ULL, 0x808080808080808ULL, 0x1010101010101010ULL, 0x2020202020202020ULL, 0x4040404040404040ULL, 0x8080808080808080ULL };

    //////helper bitboards//////
    uint64_t black;
    uint64_t white;
    uint64_t empty;
    ////////////////////////////

    std::vector<OneMove> generateWPMoves(uint64_t (&bitboards)[12]);
};


#endif //CHESSALGORITHMBITBOARDS_MOVESGENERATION_H
