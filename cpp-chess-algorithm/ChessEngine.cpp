#include "ChessEngine.h"
#include "chess-board/MovesGeneration.h"
#include <cstdlib>

OneMove ChessEngine::getBestMove(Board &board, PlayerType player) {
    MovesGeneration moves_gener;
    OneMove best_move;

    std::vector<OneMove> possible_moves = moves_gener.generatePossibleMoves(board, player);
    if (possible_moves.empty())
        return best_move;

    int r_indx = rand() % possible_moves.size();
    best_move = possible_moves.at(r_indx);

    return best_move;
}
