#ifndef CHESSALGORITHMBITBOARDS_BOARD_H
#define CHESSALGORITHMBITBOARDS_BOARD_H


#include <cstdint>
#include <string>
#include "OneMove.h"
#include "ChessEnums.h"

class Board {
public:
    // read left-to-right and top-to-bottom (index by enum PieceType)
    uint64_t bitboards[12];
    // contains if castling is possible (index by enum CastlingType)
    bool castling[4];

    Board();
    static void bitboardsToArray(char (&dest_board)[8][8], uint64_t (&bitboards)[12]);
    std::string getFENBoard();

    void movePiece(OneMove move);

private:
    void arrayToBitboards(char (&src_board)[8][8]);

    static PieceType charToPieceEnum(char char_piece);
    static char pieceEnumToChar(PieceType piece_type);
};


#endif //CHESSALGORITHMBITBOARDS_BOARD_H
