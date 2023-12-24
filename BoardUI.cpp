#include <iostream>
#include <cstring>
#include "BoardUI.h"
#include "Board.h"

void BoardUI::drawBoard(char (&board)[8][8], bool show_indexes) {
    if (show_indexes)
        std::cout << "    0 1 2 3 4 5 6 7" << std::endl << std::endl;
    else
        std::cout << "    A B C D E F G H" << std::endl << std::endl;


    for (int i = 0; i < 8; i++) {
        if (show_indexes)
            std::cout << i << "   ";
        else
            std::cout << 8 - i << "   ";

        for (int j = 0; j < 8; j++) {
            char c = board[i][j];
            if (c == ' ') c = '.';

            std::cout << c;

            if (j < 7)
                std::cout << ' ';
        }

        std::cout << std::endl;
    }
}

void BoardUI::drawBitboards(uint64_t (&bitboards)[12], bool show_indexes) {
    char board[8][8];
    Board::bitboardsToArray(board, bitboards);
    drawBoard(board, show_indexes);
}

void BoardUI::printMoves(std::vector<OneMove> moves) {
    for (OneMove move : moves) {
        std::cout << static_cast<int>(move.i1) << " " << static_cast<int>(move.j1) << "  "
        << static_cast<int>(move.i2) << " " << static_cast<int>(move.j2) << "  Promotion: " << move.promotion << std::endl;
    }
}

void BoardUI::drawBitboard(uint64_t bitboard) {
    uint64_t bitboards[12];
    memset(bitboards, 0, sizeof(bitboards));
    bitboards[0] = bitboard;

    drawBitboards(bitboards, true);
}
