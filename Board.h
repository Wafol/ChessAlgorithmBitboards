#ifndef CHESSALGORITHMBITBOARDS_BOARD_H
#define CHESSALGORITHMBITBOARDS_BOARD_H


#include <cstdint>
#include <string>
#include "OneMove.h"
#include "PieceType.h"

class Board {
public:
    //read left-to-right and top-to-bottom
    uint64_t bitboards[12];
    bool castle_wk, castle_wq, castle_bk, castle_bq = true;

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
