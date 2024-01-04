#include <iostream>
#include <bitset>
#include <fstream>
#include "chess-board/Board.h"
#include "chess-board/BoardUI.h"
#include "chess-board/MovesGeneration.h"
#include "chess-board/OneMove.h"
#include "ChessEngine.h"

int main() {
    Board board;
    BoardUI::initCommunication();

    BoardUI::writeInfoToCommunicationFile(board);

    while (true) {
        if (BoardUI::checkForMoveFromPython(board)) {

            OneMove best_move = ChessEngine::getBestMove(board, board.on_turn);
            board.movePiece(best_move);

            BoardUI::writeInfoToCommunicationFile(board);

            if (board.game_over) {
                std::cout << "GAME OVER" << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
