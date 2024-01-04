#ifndef CHESSALGORITHMBITBOARDS_CHESSENGINE_H
#define CHESSALGORITHMBITBOARDS_CHESSENGINE_H


#include "chess-board/OneMove.h"
#include "chess-board/Board.h"

class ChessEngine {
public:
    static OneMove getBestMove(Board &board, PlayerType player);
};


#endif //CHESSALGORITHMBITBOARDS_CHESSENGINE_H
