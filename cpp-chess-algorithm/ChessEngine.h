#ifndef CHESSALGORITHMBITBOARDS_CHESSENGINE_H
#define CHESSALGORITHMBITBOARDS_CHESSENGINE_H


#include "chess-board/OneMove.h"
#include "chess-board/Board.h"
#include "chess-board/MovesGeneration.h"

class ChessEngine {
public:
    OneMove getBestMove(Board &board);
    OneMove getBestMoveRandomly(Board &board, PlayerType player);
    int search(int depth, int alpha, int beta, Board board);

    //returns evaluation of position in bitboards INPUT COPIED BOARD IT WILL BE CHENGED
    int evaluatePosition(Board &board);
    uint8_t countSetBits(uint64_t n);

private:
    MovesGeneration moves_gener;

    OneMove _best_move;
    int pos_counter;

    const int pawn_val = 100;
    const int knight_val = 300;
    const int bishop_val = 300;
    const int rook_val = 500;
    const int queen_val = 900;

    //const int piece_vals[12] = {100, 500, 300, 320, 900, INT_MAX, 100, 500, 300, 320, 900, INT_MAX}; //P=0, R=1, N=2, B=3, Q=4, K=5, p=6, r=7, n=8, b=9, q=10, k=11
};


#endif //CHESSALGORITHMBITBOARDS_CHESSENGINE_H
