#ifndef CHESSALGORITHMBITBOARDS_BOARD_H
#define CHESSALGORITHMBITBOARDS_BOARD_H


#include <cstdint>

class Board {
public:
    //UPPERCASE=WHITE, lowercase=black
    typedef enum PieceType {
        P=0, R=1, N=2, B=3, Q=4, K=5, p=6, r=7, n=8, b=9, q=10, k=11, NONE
    } PieceType;

    //read left-to-right and top-to-bottom
    uint64_t bitboards[12];

    Board();

    static void bitboardsToArray(char (&dest_board)[8][8], uint64_t (&bitboards)[12]);

private:
    void arrayToBitboards(char (&src_board)[8][8]);

    static PieceType charToPieceEnum(char char_piece);
    static char pieceEnumToChar(PieceType piece_type);
};


#endif //CHESSALGORITHMBITBOARDS_BOARD_H
