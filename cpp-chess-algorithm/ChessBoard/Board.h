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
    // contains if castling is possible (index by enum CastlingType) - default is true
    bool castling[4];

    Board();
    static void bitboardsToArray(char (&dest_board)[8][8], uint64_t (&bitboards)[12]);
    std::string getFENBoard();

    void movePiece(OneMove move);

private:
    void arrayToBitboards(char (&src_board)[8][8]);

    //call when making a move, RETURNS if castling was performed
    bool handleCastling(char (&board)[8][8], OneMove move);
    void updateCastlingBoolsAfterMove(char moved_piece, OneMove move);

    static PieceType charToPieceEnum(char char_piece);
    static char pieceEnumToChar(PieceType piece_type);
};


#endif //CHESSALGORITHMBITBOARDS_BOARD_H
