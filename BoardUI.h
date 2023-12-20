#ifndef CHESSALGORITHMBITBOARDS_BOARDUI_H
#define CHESSALGORITHMBITBOARDS_BOARDUI_H

#include <vector>
#include "OneMove.h"

class BoardUI {
public:
    //if show_indexes=false, then it will draw normal chess description
    static void drawBoard(char (&board)[8][8], bool show_indexes = false);
    static void drawBitboards(uint64_t (&bitboards)[12], bool show_indexes = false);

    static void printMoves(std::vector<OneMove> moves);

private:

};


#endif //CHESSALGORITHMBITBOARDS_BOARDUI_H
