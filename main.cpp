#include <iostream>
#include <bitset>
#include "Board.h"
#include "BoardUI.h"

int main() {
    Board board;

    for (int i = 0; i < 12; i++) {
        std::cout << std::bitset<64>(board.bitboards[i]) << std::endl;
    }

    char char_board[8][8];

    board.bitboardsToArray(char_board);
    BoardUI::drawBoard(char_board);



    return 0;
}
