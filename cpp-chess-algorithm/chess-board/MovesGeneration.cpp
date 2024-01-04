#include <deque>
#include <iostream>
#include "MovesGeneration.h"
#include "BoardUI.h"

std::vector<OneMove> MovesGeneration::generatePossibleMoves(Board &board, PlayerType for_player) {
    std::vector<OneMove> pseudo_poss_moves;

    switch (for_player) {
        case WHITE:
            pseudo_poss_moves = generatePseudoWhiteMoves(board.bitboards, board.castling);
            break;
        case BLACK:
            pseudo_poss_moves = generatePseudoBlackMoves(board.bitboards, board.castling);
            break;
        case BOTH:
            pseudo_poss_moves = generatePseudoPossibleMoves(board.bitboards, board.castling);
            break;
    }

    std::vector<OneMove> possible_moves;

    for (OneMove move : pseudo_poss_moves) {
        if (isMoveLegal(move, board.bitboards)) {
            possible_moves.push_back(move);
        }
    }

    return possible_moves;
}

bool MovesGeneration::isMoveLegal(OneMove move, uint64_t (&bitboards)[12]) {
    uint64_t moved_bitboards[12];
    std::copy(std::begin(bitboards), std::end(bitboards), std::begin(moved_bitboards));

    PieceType moved_piece = Board::makeMoveInBitboards(move ,moved_bitboards);

    if (moved_piece <= 5) { //WHITE piece
        return !(unsafeForWhite(moved_bitboards)&moved_bitboards[K]);
    } else { //BLACK piece
        return !(unsafeForBlack(moved_bitboards)&moved_bitboards[k]);
    }
}

std::vector<OneMove> MovesGeneration::generatePseudoPossibleMoves(uint64_t (&bitboards)[12], bool (&castling)[4]) {
    std::vector<OneMove> white_moves = generatePseudoWhiteMoves(bitboards, castling);
    std::vector<OneMove> black_moves = generatePseudoBlackMoves(bitboards, castling);

    std::vector<OneMove> all_moves;
    all_moves.insert(all_moves.end(), white_moves.begin(), white_moves.end());
    all_moves.insert(all_moves.end(), black_moves.begin(), black_moves.end());
    return all_moves;
}

std::vector<OneMove> MovesGeneration::generatePseudoWhiteMoves(uint64_t (&bitboards)[12], bool (&castling)[4]) {
    my_pieces = (bitboards[P]|bitboards[R]|bitboards[N]|bitboards[B]|bitboards[Q]|bitboards[K]);
    enemy_pieces = (bitboards[p]|bitboards[r]|bitboards[n]|bitboards[b]|bitboards[q]|bitboards[k]);
    enemy_king = bitboards[k];
    empty = ~(my_pieces|enemy_pieces);
    occupied = ~empty;

    std::vector<OneMove> white_pawn_moves = generateWhitePawnMoves(bitboards[P]);
    std::vector<OneMove> white_rook_moves = generateRookMoves(bitboards[R]);
    std::vector<OneMove> white_bishop_moves = generateBishopMoves(bitboards[B]);
    std::vector<OneMove> white_queen_moves = generateQueenMoves(bitboards[Q]);
    std::vector<OneMove> white_knight_moves = generateKnightMoves(bitboards[N]);
    std::vector<OneMove> white_king_moves = generateKingMoves(bitboards[K]);
    std::vector<OneMove> white_castling_moves = generateWhiteCastling(bitboards, castling);

    std::vector<OneMove> white_moves;
    white_moves.insert(white_moves.end(), white_pawn_moves.begin(), white_pawn_moves.end());
    white_moves.insert(white_moves.end(), white_rook_moves.begin(), white_rook_moves.end());
    white_moves.insert(white_moves.end(), white_bishop_moves.begin(), white_bishop_moves.end());
    white_moves.insert(white_moves.end(), white_queen_moves.begin(), white_queen_moves.end());
    white_moves.insert(white_moves.end(), white_knight_moves.begin(), white_knight_moves.end());
    white_moves.insert(white_moves.end(), white_king_moves.begin(), white_king_moves.end());
    white_moves.insert(white_moves.end(), white_castling_moves.begin(), white_castling_moves.end());

    return white_moves;
}
std::vector<OneMove> MovesGeneration::generatePseudoBlackMoves(uint64_t (&bitboards)[12], bool (&castling)[4]) {
    my_pieces = (bitboards[p]|bitboards[r]|bitboards[n]|bitboards[b]|bitboards[q]|bitboards[k]);
    enemy_pieces = (bitboards[P]|bitboards[R]|bitboards[N]|bitboards[B]|bitboards[Q]|bitboards[K]);
    enemy_king = bitboards[K];
    empty = ~(my_pieces|enemy_pieces);
    occupied = ~empty;

    std::vector<OneMove> black_pawn_moves = generateBlackPawnMoves(bitboards[p]);
    std::vector<OneMove> black_rook_moves = generateRookMoves(bitboards[r]);
    std::vector<OneMove> black_bishop_moves = generateBishopMoves(bitboards[b]);
    std::vector<OneMove> black_queen_moves = generateQueenMoves(bitboards[q]);
    std::vector<OneMove> black_knight_moves = generateKnightMoves(bitboards[n]);
    std::vector<OneMove> black_king_moves = generateKingMoves(bitboards[k]);
    std::vector<OneMove> black_castling_moves = generateBlackCastling(bitboards, castling);

    std::vector<OneMove> black_moves;
    black_moves.insert(black_moves.end(), black_pawn_moves.begin(), black_pawn_moves.end());
    black_moves.insert(black_moves.end(), black_rook_moves.begin(), black_rook_moves.end());
    black_moves.insert(black_moves.end(), black_bishop_moves.begin(), black_bishop_moves.end());
    black_moves.insert(black_moves.end(), black_queen_moves.begin(), black_queen_moves.end());
    black_moves.insert(black_moves.end(), black_knight_moves.begin(), black_knight_moves.end());
    black_moves.insert(black_moves.end(), black_king_moves.begin(), black_king_moves.end());
    black_moves.insert(black_moves.end(), black_castling_moves.begin(), black_castling_moves.end());

    return black_moves;
}

std::vector<OneMove> MovesGeneration::generateWhitePawnMoves(uint64_t wpawn_bitboard) {
    std::vector<OneMove> possible_moves;

    uint64_t moves_bitboard;
    ///one step forward///
    moves_bitboard = (wpawn_bitboard >> 8) & empty & (~rank_masks[7]); //I will handle promotions later
    std::vector<OneMove> one_step_forward = getMovesFromPossibilitiesBitboard(moves_bitboard, 1, 0);
    possible_moves.insert(possible_moves.begin(), one_step_forward.begin(), one_step_forward.end());

    ///diag right///
    moves_bitboard = (wpawn_bitboard >> 7) & enemy_pieces & (~enemy_king) & (~file_masks[0]) & (~rank_masks[7]);
    std::vector<OneMove> diag_right = getMovesFromPossibilitiesBitboard(moves_bitboard, 1, -1);
    possible_moves.insert(possible_moves.begin(), diag_right.begin(), diag_right.end());

    ///diag left///
    moves_bitboard = (wpawn_bitboard >> 9) & enemy_pieces & (~enemy_king) & (~file_masks[7]) & (~rank_masks[7]);
    std::vector<OneMove> diag_left = getMovesFromPossibilitiesBitboard(moves_bitboard, 1, 1);
    possible_moves.insert(possible_moves.begin(), diag_left.begin(), diag_left.end());

    ///two steps forward///
    moves_bitboard = ((wpawn_bitboard >> 16) & empty & (empty >> 8)) & rank_masks[3];
    std::vector<OneMove> two_steps_forward = getMovesFromPossibilitiesBitboard(moves_bitboard, 2, 0);
    possible_moves.insert(possible_moves.begin(), two_steps_forward.begin(), two_steps_forward.end());

    ///promotions///
    std::vector<PieceType> poss_promotions = {Q, R, B, N};
    ///promotions - one step forward///
    moves_bitboard = (wpawn_bitboard >> 8) & empty & rank_masks[7];
    std::vector<OneMove> one_forward_promotions = getMovesFromPossibilitiesBitboard(moves_bitboard, 1, 0, poss_promotions);
    possible_moves.insert(possible_moves.begin(), one_forward_promotions.begin(), one_forward_promotions.end());
    ///promotions - diag right///
    moves_bitboard = (wpawn_bitboard >> 7) & enemy_pieces & (~enemy_king) & (~file_masks[0]) & rank_masks[7];
    std::vector<OneMove> diag_right_promotions = getMovesFromPossibilitiesBitboard(moves_bitboard, 1, -1, poss_promotions);
    possible_moves.insert(possible_moves.begin(), diag_right_promotions.begin(), diag_right_promotions.end());
    ///promotions - diag left///
    moves_bitboard = (wpawn_bitboard >> 9) & enemy_pieces & (~enemy_king) & (~file_masks[7]) & rank_masks[7];
    std::vector<OneMove> diag_left_promotions = getMovesFromPossibilitiesBitboard(moves_bitboard, 1, 1, poss_promotions);
    possible_moves.insert(possible_moves.begin(), diag_left_promotions.begin(), diag_left_promotions.end());

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateBlackPawnMoves(uint64_t bpawn_bitboard) {
    std::vector<OneMove> possible_moves;

    uint64_t moves_bitboard;
    ///one step forward///
    moves_bitboard = (bpawn_bitboard << 8) & empty & (~rank_masks[0]); //I will handle promotions later
    std::vector<OneMove> one_step_forward = getMovesFromPossibilitiesBitboard(moves_bitboard, -1, 0);
    possible_moves.insert(possible_moves.begin(), one_step_forward.begin(), one_step_forward.end());

    ///diag right/// -from the black perspective (white perspective rotated 180 deg)
    moves_bitboard = (bpawn_bitboard << 7) & enemy_pieces & (~enemy_king) & (~file_masks[7]) & (~rank_masks[0]);
    std::vector<OneMove> diag_right = getMovesFromPossibilitiesBitboard(moves_bitboard, -1, 1);
    possible_moves.insert(possible_moves.begin(), diag_right.begin(), diag_right.end());

    ///diag left///
    moves_bitboard = (bpawn_bitboard << 9) & enemy_pieces & (~enemy_king) & (~file_masks[0]) & (~rank_masks[0]);
    std::vector<OneMove> diag_left = getMovesFromPossibilitiesBitboard(moves_bitboard, -1, -1);
    possible_moves.insert(possible_moves.begin(), diag_left.begin(), diag_left.end());

    ///two steps forward///
    moves_bitboard = ((bpawn_bitboard << 16) & empty & (empty << 8)) & rank_masks[4];
    std::vector<OneMove> two_steps_forward = getMovesFromPossibilitiesBitboard(moves_bitboard, -2, 0);
    possible_moves.insert(possible_moves.begin(), two_steps_forward.begin(), two_steps_forward.end());

    ///promotions///
    std::vector<PieceType> poss_promotions = {q, r, b, n};
    ///promotions - one step forward///
    moves_bitboard = (bpawn_bitboard << 8) & empty & rank_masks[0];
    std::vector<OneMove> one_forward_promotions = getMovesFromPossibilitiesBitboard(moves_bitboard, -1, 0, poss_promotions);
    possible_moves.insert(possible_moves.begin(), one_forward_promotions.begin(), one_forward_promotions.end());
    ///promotions - diag right///
    moves_bitboard = (bpawn_bitboard << 7) & enemy_pieces & (~enemy_king) & (~file_masks[7]) & rank_masks[0];
    std::vector<OneMove> diag_right_promotions = getMovesFromPossibilitiesBitboard(moves_bitboard, -1, 1, poss_promotions);
    possible_moves.insert(possible_moves.begin(), diag_right_promotions.begin(), diag_right_promotions.end());
    ///promotions - diag left///
    moves_bitboard = (bpawn_bitboard << 9) & enemy_pieces & (~enemy_king) & (~file_masks[0]) & rank_masks[0];
    std::vector<OneMove> diag_left_promotions = getMovesFromPossibilitiesBitboard(moves_bitboard, -1, -1, poss_promotions);
    possible_moves.insert(possible_moves.begin(), diag_left_promotions.begin(), diag_left_promotions.end());

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::getMovesFromPossibilitiesBitboard(uint64_t moves_bitboard, int i1_plus, int j1_plus, const std::vector<PieceType>& possible_promotions) {
    std::vector<OneMove> possible_moves;

    uint64_t possibility = moves_bitboard & (~(moves_bitboard - 1));
    while (possibility != 0) {
        int indx = __builtin_ctzll(possibility);

        if (possible_promotions.empty()) {
            OneMove new_move(indx / 8 + i1_plus, indx % 8 + j1_plus, indx / 8, indx % 8);
            possible_moves.push_back(new_move);
        }

        for (PieceType promotion : possible_promotions) {
            OneMove new_move(indx / 8 + i1_plus, indx % 8 + j1_plus, indx / 8, indx % 8, promotion);
            possible_moves.push_back(new_move);
        }

        moves_bitboard &= ~possibility;
        possibility = moves_bitboard & (~(moves_bitboard - 1));
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateRookMoves(uint64_t rook_bitboard) {
    std::vector<OneMove> possible_moves;

    uint64_t i = rook_bitboard & ~(rook_bitboard - 1);
    uint64_t possibility;

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = HAndVMoves(piece_shift) & ~my_pieces & ~enemy_king;

        uint64_t j = possibility & ~(possibility - 1);

        while (j != 0) {
            int move_shift = __builtin_ctzll(j);
            possible_moves.emplace_back(piece_shift/8, piece_shift%8, move_shift/8, move_shift%8);

            possibility &= ~j;
            j = possibility & ~(possibility - 1);
        }

        rook_bitboard &= ~i;
        i = rook_bitboard & ~(rook_bitboard - 1);
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateBishopMoves(uint64_t bishop_bitboard) {
    std::vector<OneMove> possible_moves;

    uint64_t i = bishop_bitboard & ~(bishop_bitboard - 1);
    uint64_t possibility;

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = DAndAntiDMoves(piece_shift) & ~my_pieces & ~enemy_king;

        uint64_t j = possibility & ~(possibility - 1);

        while (j != 0) {
            int move_shift = __builtin_ctzll(j);
            possible_moves.emplace_back(piece_shift/8, piece_shift%8, move_shift/8, move_shift%8);

            possibility &= ~j;
            j = possibility & ~(possibility - 1);
        }

        bishop_bitboard &= ~i;
        i = bishop_bitboard & ~(bishop_bitboard - 1);
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateQueenMoves(uint64_t queen_bitboard) {
    std::vector<OneMove> possible_moves;

    uint64_t i = queen_bitboard & ~(queen_bitboard - 1);
    uint64_t possibility;

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = (HAndVMoves(piece_shift)|DAndAntiDMoves(piece_shift)) & ~my_pieces & ~enemy_king;

        uint64_t j = possibility & ~(possibility - 1);

        while (j != 0) {
            int move_shift = __builtin_ctzll(j);
            possible_moves.emplace_back(piece_shift/8, piece_shift%8, move_shift/8, move_shift%8);

            possibility &= ~j;
            j = possibility & ~(possibility - 1);
        }

        queen_bitboard &= ~i;
        i = queen_bitboard & ~(queen_bitboard - 1);
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateKnightMoves(uint64_t knight_bitboards) {
    std::vector<OneMove> possible_moves;

    uint64_t i = knight_bitboards & ~(knight_bitboards - 1);
    uint64_t possibility;

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);

        if (piece_shift > 45) {
            possibility = knight_span << (piece_shift - 45);
        } else {
            possibility = knight_span >> (45 - piece_shift);
        }

        if (piece_shift%8 < 4) {
            possibility &= ~file_gh & ~my_pieces & ~enemy_king;
        } else {
            possibility &= ~file_ab & ~my_pieces & ~enemy_king;
        }

        uint64_t j = possibility & ~(possibility - 1);
        while (j != 0) {
            int move_shift = __builtin_ctzll(j);
            possible_moves.emplace_back(piece_shift/8, piece_shift%8, move_shift/8, move_shift%8);

            possibility &= ~j;
            j = possibility & ~(possibility - 1);
        }

        knight_bitboards &= ~i;
        i = knight_bitboards & ~(knight_bitboards - 1);
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateKingMoves(uint64_t king_bitboard) {
    std::vector<OneMove> possible_moves;

    int piece_shift = __builtin_ctzll(king_bitboard);
    uint64_t possibility;

    if (piece_shift > 54) {
        possibility = king_span << (piece_shift - 54);
    } else {
        possibility = king_span >> (54 - piece_shift);
    }

    if (piece_shift%8 < 4) {
        possibility &= ~file_gh & ~my_pieces & ~enemy_king;
    } else {
        possibility &= ~file_ab & ~my_pieces & ~enemy_king;
    }

    uint64_t j = possibility & ~(possibility - 1);
    while (j != 0) {
        int move_shift = __builtin_ctzll(j);
        possible_moves.emplace_back(piece_shift/8, piece_shift%8, move_shift/8, move_shift%8);

        possibility &= ~j;
        j = possibility & ~(possibility - 1);
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateWhiteCastling(uint64_t (&bitboards)[12], bool (&castling)[4]) {
    std::vector<OneMove> possible_moves;
    uint64_t unsafe = unsafeForWhite(bitboards);

    if ((unsafe & bitboards[K]) == 0) {
        if (castling[CASTLE_WK] && ((1ULL<<castle_rooks[CASTLE_WK]) & bitboards[R]) != 0) {
            if (((occupied|unsafe) & ((1ULL<<61)|(1ULL<<62))) == 0) {
                possible_moves.emplace_back(7, 4, 7, 6);
            }
        }

        if (castling[CASTLE_WQ] && (((1ULL<<castle_rooks[CASTLE_WQ]) & bitboards[R]) != 0)) {
            if (((occupied|(unsafe & ~(1ULL<<57))) & ((1ULL<<57)|(1ULL<<58)|(1ULL<<59))) == 0) {
                possible_moves.emplace_back(7, 4, 7, 2);
            }
        }
    }

    return possible_moves;
}
std::vector<OneMove> MovesGeneration::generateBlackCastling(uint64_t (&bitboards)[12], bool (&castling)[4]) {
    std::vector<OneMove> possible_moves;
    uint64_t unsafe = unsafeForBlack(bitboards);

    if ((unsafe & bitboards[k]) == 0) {
        if (castling[CASTLE_BK] && ((1ULL<<castle_rooks[CASTLE_BK]) & bitboards[r]) != 0) {
            if (((occupied|unsafe) & ((1ULL<<5)|(1ULL<<6))) == 0) {
                possible_moves.emplace_back(0, 4, 0, 6);
            }
        }

        if (castling[CASTLE_BQ] && (((1ULL<<castle_rooks[CASTLE_BQ]) & bitboards[r]) != 0)) {
            if (((occupied|(unsafe & ~(1ULL<<1))) & ((1ULL<<1)|(1ULL<<2)|(1ULL<<3))) == 0) {
                possible_moves.emplace_back(0, 4, 0, 2);
            }
        }
    }

    return possible_moves;
}

uint64_t MovesGeneration::unsafeForWhite(uint64_t (&bitboards)[12]) {
    my_pieces = (bitboards[P]|bitboards[R]|bitboards[N]|bitboards[B]|bitboards[Q]|bitboards[K]);
    enemy_pieces = (bitboards[p]|bitboards[r]|bitboards[n]|bitboards[b]|bitboards[q]|bitboards[k]);
    occupied = (my_pieces|enemy_pieces);
    uint64_t unsafe;

    //pawn
    unsafe = ((bitboards[p]<<7) & ~file_masks[7]);
    unsafe |= ((bitboards[p]<<9) & ~file_masks[0]);

    //knight
    uint64_t possibility;
    uint64_t bn_bitboard = bitboards[n];
    uint64_t i = bn_bitboard & ~(bn_bitboard - 1);

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);

        if (piece_shift > 45) {
            possibility = knight_span << (piece_shift - 45);
        } else {
            possibility = knight_span >> (45 - piece_shift);
        }

        if (piece_shift%8 < 4) {
            possibility &= ~file_gh;
        } else {
            possibility &= ~file_ab;
        }

        unsafe |= possibility;

        bn_bitboard &= ~i;
        i = bn_bitboard & ~(bn_bitboard - 1);
    }

    //bishop/queen
    uint64_t bishop_queen = bitboards[b]|bitboards[q];
    i = bishop_queen & ~(bishop_queen - 1);

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = DAndAntiDMoves(piece_shift);

        unsafe |= possibility;

        bishop_queen &= ~i;
        i = bishop_queen & ~(bishop_queen - 1);
    }

    //rook/queen
    uint64_t rook_queen = bitboards[r]|bitboards[q];
    i = rook_queen & ~(rook_queen - 1);

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = HAndVMoves(piece_shift);

        unsafe |= possibility;

        rook_queen &= ~i;
        i = rook_queen & ~(rook_queen - 1);
    }

    //king
    int piece_shift = __builtin_ctzll(bitboards[k]);

    if (piece_shift > 54) {
        possibility = king_span << (piece_shift - 54);
    } else {
        possibility = king_span >> (54 - piece_shift);
    }

    if (piece_shift%8 < 4) {
        possibility &= ~file_gh;
    } else {
        possibility &= ~file_ab;
    }

    unsafe |= possibility;

    return unsafe;
}
uint64_t MovesGeneration::unsafeForBlack(uint64_t (&bitboards)[12]) {
    my_pieces = (bitboards[P]|bitboards[R]|bitboards[N]|bitboards[B]|bitboards[Q]|bitboards[K]);
    enemy_pieces = (bitboards[p]|bitboards[r]|bitboards[n]|bitboards[b]|bitboards[q]|bitboards[k]);
    occupied = (my_pieces|enemy_pieces);
    uint64_t unsafe;

    //pawn
    unsafe = ((bitboards[P]>>7) & ~file_masks[0]);
    unsafe |= ((bitboards[P]>>9) & ~file_masks[7]);

    //knight
    uint64_t possibility;
    uint64_t bn_bitboard = bitboards[N];
    uint64_t i = bn_bitboard & ~(bn_bitboard - 1);

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);

        if (piece_shift > 45) {
            possibility = knight_span << (piece_shift - 45);
        } else {
            possibility = knight_span >> (45 - piece_shift);
        }

        if (piece_shift%8 < 4) {
            possibility &= ~file_gh;
        } else {
            possibility &= ~file_ab;
        }

        unsafe |= possibility;

        bn_bitboard &= ~i;
        i = bn_bitboard & ~(bn_bitboard - 1);
    }

    //bishop/queen
    uint64_t bishop_queen = bitboards[B]|bitboards[Q];
    i = bishop_queen & ~(bishop_queen - 1);

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = DAndAntiDMoves(piece_shift);

        unsafe |= possibility;

        bishop_queen &= ~i;
        i = bishop_queen & ~(bishop_queen - 1);
    }

    //rook/queen
    uint64_t rook_queen = bitboards[R]|bitboards[Q];
    i = rook_queen & ~(rook_queen - 1);

    while(i != 0) {
        int piece_shift = __builtin_ctzll(i);
        possibility = HAndVMoves(piece_shift);

        unsafe |= possibility;

        rook_queen &= ~i;
        i = rook_queen & ~(rook_queen - 1);
    }

    //king
    int piece_shift = __builtin_ctzll(bitboards[K]);

    if (piece_shift > 54) {
        possibility = king_span << (piece_shift - 54);
    } else {
        possibility = king_span >> (54 - piece_shift);
    }

    if (piece_shift%8 < 4) {
        possibility &= ~file_gh;
    } else {
        possibility &= ~file_ab;
    }

    unsafe |= possibility;

    return unsafe;
}

uint64_t MovesGeneration::DAndAntiDMoves(int piece_shift) {
    uint64_t piece_bitboard = 1ULL<<piece_shift;

    uint64_t diag_mask = diag_masks[(piece_shift / 8) + (7 - piece_shift % 8)];
    uint64_t possible_diagonal = ((occupied & diag_mask) - 2*piece_bitboard) ^ reverseBits(reverseBits(occupied & diag_mask) - 2*reverseBits(piece_bitboard));

    uint64_t  anti_diag_mask = anti_diag_masks[(piece_shift/8) + (piece_shift%8)];
    uint64_t possible_anti_diagonal = ((occupied & anti_diag_mask) - 2*piece_bitboard) ^ reverseBits(reverseBits(occupied & anti_diag_mask) - 2*reverseBits(piece_bitboard));

    return (possible_diagonal&diag_mask) | (possible_anti_diagonal&anti_diag_mask);
}
uint64_t MovesGeneration::HAndVMoves(int piece_shift) {
    uint64_t piece_bitboard = 1ULL<<piece_shift;

    uint64_t possible_horizontal = (occupied - 2*piece_bitboard) ^ reverseBits(reverseBits(occupied) - 2*reverseBits(piece_bitboard));
    uint64_t possible_vertical = ((occupied & file_masks[piece_shift % 8]) - 2*piece_bitboard) ^ reverseBits(reverseBits(occupied & file_masks[piece_shift % 8]) - 2*reverseBits(piece_bitboard));

    return (possible_horizontal & rank_masks[7 - piece_shift/8]) | (possible_vertical & file_masks[piece_shift % 8]);
}

uint64_t MovesGeneration::reverseBits(uint64_t x) {
    //https://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious

    uint64_t r = x; // r will be reversed bits of v; first get LSB of v
    int s = sizeof(x) * 64 - 1; // extra shift needed at end

    for (x >>= 1; x; x >>= 1) {
        r <<= 1;
        r |= x & 1;
        s--;
    }
    r <<= s; // shift when v's highest bits are zero
    return r;
}




















