#ifndef CHESSALGORITHMBITBOARDS_MOVESGENERATION_H
#define CHESSALGORITHMBITBOARDS_MOVESGENERATION_H


#include <cstdint>
#include <vector>
#include "Board.h"
#include "OneMove.h"

class MovesGeneration {
public:
    std::vector<OneMove> generatePossibleMoves(Board &board, PlayerType for_player);

    bool isWhiteKingInCheck(uint64_t (&bitboards)[12]);
    bool isBlackKingInCheck(uint64_t (&bitboards)[12]);
private:
    uint64_t rank_masks[8] = { 0xFF00000000000000ULL, 0xFF000000000000ULL, 0xFF0000000000ULL, 0xFF00000000ULL, 0xFF000000ULL, 0xFF0000ULL, 0xFF00ULL, 0xFFULL };
    uint64_t file_masks[8] { 0x101010101010101ULL, 0x202020202020202ULL, 0x404040404040404ULL, 0x808080808080808ULL, 0x1010101010101010ULL, 0x2020202020202020ULL, 0x4040404040404040ULL, 0x8080808080808080ULL };
    // from top left to bottom right
    uint64_t diag_masks[15] = { 0x80L, 0x8040L, 0x804020L, 0x80402010L, 0x8040201008L, 0x804020100804L, 0x80402010080402L, 0x8040201008040201L, 0x4020100804020100L, 0x2010080402010000L, 0x1008040201000000L, 0x804020100000000L, 0x402010000000000L, 0x201000000000000L, 0x100000000000000L };
    // from top right to bottom left
    uint64_t anti_diag_masks[15] = { 0x1ULL, 0x102ULL, 0x10204ULL, 0x1020408ULL, 0x102040810ULL, 0x10204081020ULL, 0x1020408102040ULL, 0x102040810204080ULL, 0x204081020408000ULL, 0x408102040800000ULL, 0x810204080000000ULL, 0x1020408000000000ULL, 0x2040800000000000ULL, 0x4080000000000000ULL, 0x8000000000000000ULL };

    //////helper bitboards//////
    uint64_t my_pieces = 0;
    uint64_t enemy_pieces = 0;
    uint64_t enemy_king = 0;
    uint64_t empty = 0;
    uint64_t occupied = 0;

    //this var stores moves when knight is on position i=5, j=5
    const uint64_t knight_span = 5802888705324613632ULL;
    const uint64_t king_span = 16186183351374184448ULL;

    const uint64_t file_gh = file_masks[6]|file_masks[7];
    const uint64_t file_ab = file_masks[0]|file_masks[1];

    //index by enum CastlingType
    const uint64_t castle_rooks[4] = {63, 56, 7, 0};
    ////////////////////////////

    std::vector<OneMove> generatePseudoPossibleMoves(uint64_t (&bitboards)[12], bool (&castling)[4]);
    bool isMoveLegal(OneMove move, uint64_t (&bitboards)[12]);

    std::vector<OneMove> generatePseudoWhiteMoves(uint64_t (&bitboards)[12], bool (&castling)[4]);
    std::vector<OneMove> generatePseudoBlackMoves(uint64_t (&bitboards)[12], bool (&castling)[4]);

    std::vector<OneMove> generateWhitePawnMoves(uint64_t wpawn_bitboard);
    std::vector<OneMove> generateBlackPawnMoves(uint64_t bpawn_bitboard);
    std::vector<OneMove> generateRookMoves(uint64_t rook_bitboard);
    std::vector<OneMove> generateBishopMoves(uint64_t bishop_bitboard);
    std::vector<OneMove> generateQueenMoves(uint64_t queen_bitboard);
    std::vector<OneMove> generateKnightMoves(uint64_t knight_bitboards);
    std::vector<OneMove> generateKingMoves(uint64_t king_bitboard);
    std::vector<OneMove> generateWhiteCastling(uint64_t (&bitboards)[12], bool (&castling)[4]);
    std::vector<OneMove> generateBlackCastling(uint64_t (&bitboards)[12], bool (&castling)[4]);

    uint64_t unsafeForWhite(uint64_t (&bitboards)[12]);
    uint64_t unsafeForBlack(uint64_t (&bitboards)[12]);

    //this function takes bitboard with all possible positions where piece could move and transfers it to vector of OneMoves
    //int i1_plus, int j1_plus are numbers that are used to get starting position from the end position of one piece possible move
    std::vector<OneMove> getMovesFromPossibilitiesBitboard(uint64_t possibilities, int i1_plus, int j1_plus, const std::vector<PieceType>& possible_promotions = {});

    uint64_t HAndVMoves(int piece_shift);
    uint64_t DAndAntiDMoves(int piece_shift);
    static uint64_t reverseBits(uint64_t x);
};


#endif //CHESSALGORITHMBITBOARDS_MOVESGENERATION_H
