#include "Board.h"
#include <cstring>

Board::Board() {
    memset(bitboards, 0, sizeof(bitboards));

    char board[8][8] = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    arrayToBitboards(board);
}

void Board::arrayToBitboards(char (&board)[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            uint64_t bin_piece_pos = 1ULL<<(j + i*8);
            PieceType piece_i = charToPieceEnum(board[i][j]);
            if (piece_i == NONE) continue;

            bitboards[piece_i] |= bin_piece_pos;
        }
    }
}

Board::PieceType Board::charToPieceEnum(char char_piece){
    switch (char_piece) {
        case 'P': return P;
        case 'R': return R;
        case 'N': return N;
        case 'B': return B;
        case 'Q': return Q;
        case 'K': return K;

        case 'p': return p;
        case 'r': return r;
        case 'n': return n;
        case 'b': return b;
        case 'q': return q;
        case 'k': return k;

        default: return NONE;
    }
}