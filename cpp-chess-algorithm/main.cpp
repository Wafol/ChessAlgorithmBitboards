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
    ChessEngine chess_engine;
    BoardUI::initCommunication();

    //std::cout << chess_engine.evaluatePosition(board) << std::endl;
    //return 0;

    BoardUI::writeInfoToCommunicationFile(board);

    while (true) {
        OneMove move_from_py = BoardUI::getMoveFromPython(board);

        if (move_from_py.valid) {
            board.movePiece(move_from_py); //PLAYERS MOVE
            board.on_turn = static_cast<PlayerType>(!board.on_turn); //switch current player
            board.updatePossibleMoves();
            GameOver game_over = board.isCheckMate();

            BoardUI::writeInfoToCommunicationFile(board);
            if (game_over != NOT_OVER) {
                std::cout << "GAME OVER" << std::endl;
                return 0;
            }


            OneMove best_move = chess_engine.getBestMove(board);
            board.movePiece(best_move); //COMPUTERS MOVE
            board.on_turn = static_cast<PlayerType>(!board.on_turn);
            board.updatePossibleMoves();
            game_over = board.isCheckMate();

            BoardUI::writeInfoToCommunicationFile(board);
            if (game_over != NOT_OVER) {
                std::cout << "GAME OVER" << std::endl;
                return 0;
            }


        }
    }

    return 0;
}
