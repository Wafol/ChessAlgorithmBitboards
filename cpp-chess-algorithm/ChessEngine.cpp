#include "ChessEngine.h"
#include "chess-board/MovesGeneration.h"
#include <cstdlib>
#include <iostream>

OneMove ChessEngine::getBestMoveRandomly(Board &board, PlayerType player) {
    OneMove best_move;

    std::vector<OneMove> possible_moves = moves_gener.generatePossibleMoves(board, player);
    if (possible_moves.empty())
        return best_move;

    int r_indx = rand() % possible_moves.size();
    best_move = possible_moves.at(r_indx);

    return best_move;
}

OneMove ChessEngine::getBestMove(Board &board) {
    Board help_board = board;
    pos_counter = 0;
    search(4, -999999999, 999999999, help_board);

    std::cout << pos_counter << std::endl;

    return _best_move;
}

int ChessEngine::search(int depth, int alpha, int beta, Board board) {
    if (depth%2 == 0) {
        board.on_turn = BLACK;
    } else {
        board.on_turn = WHITE;
    }

    if (depth == 0) {
        return evaluatePosition(board);
    }

    std::vector<OneMove> possible_moves = moves_gener.generatePossibleMoves(board, board.on_turn);

    //BoardUI::printMoves(possible_moves);

    if (possible_moves.empty()) {
        if (board.isPlayerInCheck(board.on_turn)) {
            return -999999999;
        }

        return 0;
    }

    int best_eval = -999999999;

    for (OneMove move : possible_moves) {
        board.movePiece(move);
        pos_counter++;

        int eval = -search(depth - 1, -beta, -alpha, board);

        if (eval > best_eval) {
            best_eval = eval;

            if (depth == 4)
                _best_move = move;
        }

        board.undoLastMove();

        if (eval >= beta) {
            return beta;
        }

        alpha = std::max(alpha, eval);
    }

    return alpha;
}

int ChessEngine::evaluatePosition(Board &board) {
    int white_eval = 0;
    int black_eval = 0;

    white_eval += countSetBits(board.bitboards[P])*pawn_val;
    white_eval += countSetBits(board.bitboards[N])*knight_val;
    white_eval += countSetBits(board.bitboards[B])*bishop_val;
    white_eval += countSetBits(board.bitboards[R])*rook_val;
    white_eval += countSetBits(board.bitboards[Q])*queen_val;

    black_eval += countSetBits(board.bitboards[p])*pawn_val;
    black_eval += countSetBits(board.bitboards[n])*knight_val;
    black_eval += countSetBits(board.bitboards[b])*bishop_val;
    black_eval += countSetBits(board.bitboards[r])*rook_val;
    black_eval += countSetBits(board.bitboards[q])*queen_val;

    /*for (int i = 0; i < 12; i++) {
        if (i <= 5) { //white piece
            if (i != K)
                white_eval += countSetBits(board.bitboards[i])*piece_vals[i];
        } else { //black piece
            if (i != k)
                black_eval += countSetBits(board.bitboards[i])*piece_vals[i];
        }
    }*/

    int eval = white_eval - black_eval;
    int perspective = (board.on_turn == WHITE) ? 1 : -1;

    return eval*perspective;
}

uint8_t ChessEngine::countSetBits(uint64_t n)  {
    uint8_t count = 0;

    while (n) {
        n &= (n - 1);
        count++;
    }

    return count;
}





