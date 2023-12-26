#include "MovesGeneration.h"
#include <iostream>
#include <bitset>
#include <cstring>
#include <immintrin.h>
#include "BoardUI.h"

std::vector<OneMove> MovesGeneration::getMovesFromPossibilitiesBitboard(uint64_t moves_bitboard, int i1_plus, int j1_plus, const std::vector<Board::PieceType>& possible_promotions) {
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

std::vector<OneMove> MovesGeneration::generateWhiteMoves(uint64_t (&bitboards)[12]) {
    my_pieces = (bitboards[Board::P]|bitboards[Board::R]|bitboards[Board::N]|bitboards[Board::B]|bitboards[Board::Q]|bitboards[Board::K]);
    enemy_pieces = (bitboards[Board::p]|bitboards[Board::r]|bitboards[Board::n]|bitboards[Board::b]|bitboards[Board::q]|bitboards[Board::k]);
    enemy_king = bitboards[Board::k];
    empty = ~(my_pieces|enemy_pieces);
    occupied = ~empty;

    std::vector<OneMove> white_pawn_moves = generateWhitePawnMoves(bitboards[Board::P]);
    std::vector<OneMove> white_rook_moves = generateRookMoves(bitboards[Board::R]);
    std::vector<OneMove> white_bishop_moves = generateBishopMoves(bitboards[Board::B]);
    std::vector<OneMove> white_queen_moves = generateQueenMoves(bitboards[Board::Q]);
    std::vector<OneMove> white_knight_moves = generateKnightMoves(bitboards[Board::N]);
    std::vector<OneMove> white_king_moves = generateKingMoves(bitboards[Board::K]);

    std::vector<OneMove> white_moves;
    white_moves.insert(white_moves.end(), white_pawn_moves.begin(), white_pawn_moves.end());
    white_moves.insert(white_moves.end(), white_rook_moves.begin(), white_rook_moves.end());
    white_moves.insert(white_moves.end(), white_bishop_moves.begin(), white_bishop_moves.end());
    white_moves.insert(white_moves.end(), white_queen_moves.begin(), white_queen_moves.end());
    white_moves.insert(white_moves.end(), white_knight_moves.begin(), white_knight_moves.end());
    white_moves.insert(white_moves.end(), white_king_moves.begin(), white_king_moves.end());

    return white_moves;
}

std::vector<OneMove> MovesGeneration::generateBlackMoves(uint64_t (&bitboards)[12]) {
    my_pieces = (bitboards[Board::p]|bitboards[Board::r]|bitboards[Board::n]|bitboards[Board::b]|bitboards[Board::q]|bitboards[Board::k]);
    enemy_pieces = (bitboards[Board::P]|bitboards[Board::R]|bitboards[Board::N]|bitboards[Board::B]|bitboards[Board::Q]|bitboards[Board::K]);
    enemy_king = bitboards[Board::K];
    empty = ~(my_pieces|enemy_pieces);
    occupied = ~empty;

    std::vector<OneMove> black_pawn_moves = generateBlackPawnMoves(bitboards[Board::p]);
    std::vector<OneMove> black_rook_moves;// = generateRookMoves(bitboards[Board::r]);
    std::vector<OneMove> black_bishop_moves;// = generateBishopMoves(bitboards[Board::b]);
    std::vector<OneMove> black_queen_moves;// = generateQueenMoves(bitboards[Board::q]);
    std::vector<OneMove> black_knight_moves;// = generateKnightMoves(bitboards[Board::n]);
    std::vector<OneMove> black_king_moves;// = generateKingMoves(bitboards[Board::k]);

    std::vector<OneMove> black_moves;
    black_moves.insert(black_moves.end(), black_pawn_moves.begin(), black_pawn_moves.end());
    black_moves.insert(black_moves.end(), black_rook_moves.begin(), black_rook_moves.end());
    black_moves.insert(black_moves.end(), black_bishop_moves.begin(), black_bishop_moves.end());
    black_moves.insert(black_moves.end(), black_queen_moves.begin(), black_queen_moves.end());
    black_moves.insert(black_moves.end(), black_knight_moves.begin(), black_knight_moves.end());
    black_moves.insert(black_moves.end(), black_king_moves.begin(), black_king_moves.end());

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
    std::vector<Board::PieceType> poss_promotions = {Board::Q, Board::R, Board::B, Board::N};
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
    std::vector<Board::PieceType> poss_promotions = {Board::q, Board::r, Board::b, Board::n};
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

    //this var stores moves when knight is on position i=5, j=5
    const uint64_t knight_span = 5802888705324613632ULL;

    const uint64_t file_gh = file_masks[6]|file_masks[7];
    const uint64_t file_ab = file_masks[0]|file_masks[1];

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

    const uint64_t king_span = 16186183351374184448ULL;

    const uint64_t file_gh = file_masks[6]|file_masks[7];
    const uint64_t file_ab = file_masks[0]|file_masks[1];

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

/*uint64_t MovesGeneration::unsafeForBlack(uint64_t *bitboards) {
    uint64_t unsafe = 0;

    //pawn
    unsafe=((WP>>>7)&~FILE_A);//pawn capture right
    unsafe|=((WP>>>9)&~FILE_H);//pawn capture left
    long possibility;
    //knight
    long i=WN&~(WN-1);
    while(i != 0)
    {
        int iLocation=Long.numberOfTrailingZeros(i);
        if (iLocation>18)
        {
            possibility=KNIGHT_SPAN<<(iLocation-18);
        }
        else {
            possibility=KNIGHT_SPAN>>(18-iLocation);
        }
        if (iLocation%8<4)
        {
            possibility &=~FILE_GH;
        }
        else {
            possibility &=~FILE_AB;
        }
        unsafe |= possibility;
        WN&=~i;
        i=WN&~(WN-1);
    }
    //bishop/queen
    long QB=WQ|WB;
    i=QB&~(QB-1);
    while(i != 0)
    {
        int iLocation=Long.numberOfTrailingZeros(i);
        possibility=DAndAntiDMoves(iLocation);
        unsafe |= possibility;
        QB&=~i;
        i=QB&~(QB-1);
    }
    //rook/queen
    long QR=WQ|WR;
    i=QR&~(QR-1);
    while(i != 0)
    {
        int iLocation=Long.numberOfTrailingZeros(i);
        possibility=HAndVMoves(iLocation);
        unsafe |= possibility;
        QR&=~i;
        i=QR&~(QR-1);
    }
    //king
    int iLocation=Long.numberOfTrailingZeros(WK);
    if (iLocation>9)
    {
        possibility=KING_SPAN<<(iLocation-9);
    }
    else {
        possibility=KING_SPAN>>(9-iLocation);
    }
    if (iLocation%8<4)
    {
        possibility &=~FILE_GH;
    }
    else {
        possibility &=~FILE_AB;
    }
    unsafe |= possibility;
    System.out.println();
    drawBitboard(unsafe);
    return unsafe;

    return 0;
}*/

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








