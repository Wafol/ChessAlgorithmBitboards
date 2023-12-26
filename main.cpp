#include <iostream>
#include <bitset>
#include "Board.h"
#include "BoardUI.h"
#include "MovesGeneration.h"
#include "OneMove.h"

int main() {
    Board board;

    //for (int i = 0; i < 12; i++) {
    //    std::cout << std::bitset<64>(board.bitboards[i]) << std::endl;
    //}

    BoardUI::drawBitboards(board.bitboards, true);

    std::cout << std::endl << std::endl;

    MovesGeneration moves_gener;
    //std::vector<OneMove> moves = moves_gener.generatePieceMoves(board.bitboards, Board::P);
    std::vector<OneMove> moves = moves_gener.generateBlackMoves(board.bitboards);



    BoardUI::printMoves(moves);



    //BoardUI::drawBoard(char_board);



    return 0;
}
