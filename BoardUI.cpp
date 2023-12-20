#include <iostream>
#include "BoardUI.h"
#include "Board.h"

void BoardUI::drawBoard(char (&board)[8][8]) {
    std::cout << "    A B C D E F G H" << std::endl << std::endl;

    for (int i = 0; i < 8; i++) {
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

void BoardUI::drawBitboards(uint64_t (&bitboards)[12]) {
    char board[8][8];
    Board::bitboardsToArray(board, bitboards);
    drawBoard(board);
}

void BoardUI::printMoves(std::vector<OneMove> moves) {
    for (OneMove move : moves) {
        std::cout << static_cast<int>(move.i1) << " " << static_cast<int>(move.j1) << " "
        << static_cast<int>(move.i2) << " " << static_cast<int>(move.j2) << std::endl;
    }
}

