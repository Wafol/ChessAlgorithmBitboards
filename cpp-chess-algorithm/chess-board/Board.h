#ifndef CHESSALGORITHMBITBOARDS_BOARD_H
#define CHESSALGORITHMBITBOARDS_BOARD_H


#include <cstdint>
#include <string>
#include <vector>
#include "OneMove.h"
#include "ChessEnums.h"

class Board {
public:
    // read left-to-right and top-to-bottom (index by enum PieceType)
    uint64_t bitboards[12];
    // contains if castling is possible (index by enum CastlingType) - default is true
    bool castling[4];

    std::vector<OneMove> possible_moves;
    PlayerType on_turn;
    bool game_over;

    Board();
    static void bitboardsToArray(char (&dest_board)[8][8], uint64_t (&bitboards)[12]);
    std::string getFENBoard();

    //this method moves piece in internal bitboards
    void movePiece(OneMove move);
    //this method is different from move Piece bcs it changes only the entered bitboard and doesnt check for check, endgame etc.
    static PieceType makeMoveInBitboards(OneMove move, uint64_t (&bitboards)[12]);//returns which piece was moved

private:
    void arrayToBitboards(char (&src_board)[8][8]);

    //call when making a move, RETURNS if castling was performed
    bool makeCastlingMove(uint64_t (&bitboards)[12], OneMove move);
    void updateCastlingBoolsAfterMove(PieceType moved_piece, OneMove move);

    static PieceType charToPieceEnum(char char_piece);
    static char pieceEnumToChar(PieceType piece_type);
};


#endif //CHESSALGORITHMBITBOARDS_BOARD_H
