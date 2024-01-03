#include <iostream>
#include <bitset>
#include <fstream>
#include "ChessBoard/Board.h"
#include "ChessBoard/BoardUI.h"
#include "ChessBoard/MovesGeneration.h"
#include "ChessBoard/OneMove.h"

int main() {
    Board board;
    BoardUI::initCommunication();

    MovesGeneration moves_gener;
    std::vector<OneMove> possible_moves = moves_gener.generatePossibleMoves(board);
    BoardUI::writeInfoToCommunicationFile(board, possible_moves);

    while (true) {
        if (BoardUI::checkForMoveFromPython(board)) {
            possible_moves = moves_gener.generatePossibleMoves(board);
            BoardUI::writeInfoToCommunicationFile(board, possible_moves);

            BoardUI::drawBitboard(moves_gener.unsafeForBlack(board.bitboards));
        }
    }

    return 0;
}
