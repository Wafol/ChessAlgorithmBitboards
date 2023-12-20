#include "MovesGeneration.h"
#include <iostream>
#include <bitset>
#include <cstring>
#include "BoardUI.h"

std::vector<OneMove> MovesGeneration::generateWPMoves(uint64_t (&bitboards)[12]) {
    std::vector<OneMove> possible_moves;

    uint64_t moves_bitboard;
    ///one step forward///
    moves_bitboard = (bitboards[Board::P]>>8) & empty & (~rank_masks[7]); //I will handle promotions later
    std::vector<OneMove> one_step_forward = getMovesFromPossibilities(moves_bitboard, 1, 0);
    possible_moves.insert(possible_moves.begin(), one_step_forward.begin(), one_step_forward.end());

    ///diag right///
    moves_bitboard = (bitboards[Board::P]>>7) & black & (~bitboards[Board::k]) & (~file_masks[0]) & (~rank_masks[7]);
    std::vector<OneMove> diag_right = getMovesFromPossibilities(moves_bitboard, 1, -1);
    possible_moves.insert(possible_moves.begin(), diag_right.begin(), diag_right.end());

    ///diag left///
    moves_bitboard = (bitboards[Board::P]>>9) & black & (~bitboards[Board::k]) & (~file_masks[7]) & (~rank_masks[7]);
    std::vector<OneMove> diag_left = getMovesFromPossibilities(moves_bitboard, 1, 1);
    possible_moves.insert(possible_moves.begin(), diag_left.begin(), diag_left.end());

    ///two steps forward///
    moves_bitboard = ((bitboards[Board::P]>>16) & empty & (empty>>8)) & rank_masks[3];
    std::vector<OneMove> two_steps_forward = getMovesFromPossibilities(moves_bitboard, 2, 0);
    possible_moves.insert(possible_moves.begin(), two_steps_forward.begin(), two_steps_forward.end());

    ///promotions///
    std::vector<Board::PieceType> poss_promotions = {Board::Q, Board::R, Board::B, Board::N};
    ///promotions - one step forward///
    moves_bitboard = (bitboards[Board::P]>>8) & empty & rank_masks[7];
    std::vector<OneMove> one_forward_promotions = getMovesFromPossibilities(moves_bitboard, 1, 0, poss_promotions);
    possible_moves.insert(possible_moves.begin(), one_forward_promotions.begin(), one_forward_promotions.end());
    ///promotions - diag right///
    moves_bitboard = (bitboards[Board::P]>>7) & black & (~bitboards[Board::k]) & (~file_masks[0]) & rank_masks[7];
    std::vector<OneMove> diag_right_promotions = getMovesFromPossibilities(moves_bitboard, 1, -1, poss_promotions);
    possible_moves.insert(possible_moves.begin(), diag_right_promotions.begin(), diag_right_promotions.end());
    ///promotions - diag left///
    moves_bitboard = (bitboards[Board::P]>>9) & black & (~bitboards[Board::k]) & (~file_masks[7]) & rank_masks[7];
    std::vector<OneMove> diag_left_promotions = getMovesFromPossibilities(moves_bitboard, 1, 1, poss_promotions);
    possible_moves.insert(possible_moves.begin(), diag_left_promotions.begin(), diag_left_promotions.end());

    /* uint64_t test_bitboards[12];
    memset(test_bitboards, 0, sizeof(test_bitboards));
    test_bitboards[Board::P] = moves_bitboard;

    BoardUI::drawBitboards(test_bitboards); */
    return possible_moves;
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

std::vector<OneMove> MovesGeneration::getMovesFromPossibilities(uint64_t moves_bitboard, int i1_plus, int j1_plus, std::vector<Board::PieceType> possible_promotions) {
    std::vector<OneMove> possible_moves;

    uint64_t possibility = moves_bitboard & (~(moves_bitboard - 1));
    while (possibility != 0) {
        int indx = __builtin_ctzll(possibility);

        if (possible_promotions.empty()) {
            OneMove new_move(indx / 8 + i1_plus, indx % 8 + j1_plus, indx / 8, indx % 8);
            possible_moves.push_back(new_move);
        }

        for (Board::PieceType promotion : possible_promotions) {
            OneMove new_move(indx / 8 + i1_plus, indx % 8 + j1_plus, indx / 8, indx % 8, promotion);
            possible_moves.push_back(new_move);
        }

        moves_bitboard &= ~possibility;
        possibility = moves_bitboard & (~(moves_bitboard - 1));
    }

    return possible_moves;
}
