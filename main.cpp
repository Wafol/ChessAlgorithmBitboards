#include <iostream>
#include <bitset>
#include <fstream>
#include "Board.h"
#include "BoardUI.h"
#include "MovesGeneration.h"
#include "OneMove.h"

int main() {
    Board board;

    //BoardUI::drawBitboards(board.bitboards, false);

    std::cout << std::endl << std::endl;

    //std::string fen = board.getFENBoard();
    //std::cout << fen;

    MovesGeneration moves_gener;
    std::vector<OneMove> possible_moves = moves_gener.generatePossibleMoves(board.bitboards);

    //

    //std::vector<OneMove> moves = moves_gener.generatePieceMoves(board.bitboards);
    //std::vector<OneMove> moves = moves_gener.generateBlackMoves(board.bitboards);

    while (true) {
        if (BoardUI::checkForMoveFromPython(board)) {
            possible_moves = moves_gener.generatePossibleMoves(board.bitboards);
        }

        BoardUI::writeInfoToCommunicationFile(board, possible_moves);
    }

    while (true) {
        std::string in;
        std::cin >> in;

        BoardUI::handlePlayerMove(in, board);

        BoardUI::drawBitboards(board.bitboards, false);

        possible_moves = moves_gener.generatePossibleMoves(board.bitboards);
        BoardUI::writeInfoToCommunicationFile(board, possible_moves);
    }

    //BoardUI::printMoves(moves);
    //BoardUI::drawBoard(char_board);

    return 0;
}
