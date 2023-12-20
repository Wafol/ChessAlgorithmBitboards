#ifndef CHESSALGORITHMBITBOARDS_BOARDUI_H
#define CHESSALGORITHMBITBOARDS_BOARDUI_H

#include <vector>
#include "OneMove.h"

class BoardUI {
public:
    static void drawBoard(char (&board)[8][8]);
    static void drawBitboards(uint64_t (&bitboards)[12]);

    static void printMoves(std::vector<OneMove> moves);
};


#endif //CHESSALGORITHMBITBOARDS_BOARDUI_H
