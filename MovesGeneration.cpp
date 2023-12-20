#include "MovesGeneration.h"
#include <iostream>
#include <bitset>
#include <cstring>
#include "BoardUI.h"

std::vector<OneMove> MovesGeneration::generateWPMoves(uint64_t (&bitboards)[12]) {
    std::vector<OneMove> moves;

    uint64_t moves_bitboard;
    ///one step forward///
    moves_bitboard = (bitboards[Board::P]>>8) & empty & (~rank_masks[7]); //I will handle promotions later

    uint64_t possibility = moves_bitboard & (~(moves_bitboard - 1));
    while (possibility != 0) {
        int indx = __builtin_ctzll(possibility);
        moves.emplace_back(indx/8 + 1, indx%8, indx/8, indx%8);
        moves_bitboard &= ~possibility;
        possibility = moves_bitboard & (~(moves_bitboard - 1));
    }

    ///diag right///
    moves_bitboard = 0;
    moves_bitboard |= (bitboards[Board::P]>>7) & black & (~bitboards[Board::k]) & (~file_masks[0]) & (~rank_masks[7]);

    ///diag left///
    moves_bitboard = 0;
    moves_bitboard |= (bitboards[Board::P]>>9) & black & (~bitboards[Board::k]) & (~file_masks[7]) & (~rank_masks[7]);

    ///two steps forward///
    moves_bitboard = 0;
    moves_bitboard |= ((bitboards[Board::P]>>16) & empty & (empty>>8)) & rank_masks[3];

    ///promotions///

    uint64_t test_bitboards[12];
    memset(test_bitboards, 0, sizeof(test_bitboards));
    test_bitboards[Board::P] = moves_bitboard;

    BoardUI::drawBitboards(test_bitboards);

    return moves;
}

std::vector<OneMove> MovesGeneration::generatePieceMoves(uint64_t (&bitboards)[12], Board::PieceType p_type) {
    black = (bitboards[Board::p]|bitboards[Board::r]|bitboards[Board::n]|bitboards[Board::b]|bitboards[Board::q]|bitboards[Board::k]);
    white = (bitboards[Board::P]|bitboards[Board::R]|bitboards[Board::N]|bitboards[Board::B]|bitboards[Board::Q]|bitboards[Board::K]);
    empty = ~(white|black);

    std::vector<OneMove> moves;

    switch (p_type) {
        case Board::P:
            moves = generateWPMoves(bitboards);
            break;
    }

    return moves;
}
