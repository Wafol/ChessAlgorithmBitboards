#ifndef CHESSALGORITHMBITBOARDS_BOARDUI_H
#define CHESSALGORITHMBITBOARDS_BOARDUI_H

#include <vector>
#include "OneMove.h"
#include "Board.h"

class BoardUI {
public:
    static void initCommunication();

    //returns if it was successful
    static bool handlePlayerMove(std::string move_input, Board &board);
    static void writeInfoToCommunicationFile(Board &board);
    //returns valid=true move if it recieves move from py
    static OneMove getMoveFromPython(Board &board);

    //if show_indexes=false, then it will draw normal chess description
    static void drawBoard(char (&board)[8][8], bool show_indexes = false);
    static void drawBitboards(uint64_t (&bitboards)[12], bool show_indexes = false);
    static void drawBitboard(uint64_t bitboard);

    static void printMoves(std::vector<OneMove> moves);

private:
    constexpr static char CPP_TO_PY_FILE[] = R"(D:\Dokumenty\_skola\DlouhodobaMaturitniPrace\ChessBoardProgram\ChessAlgorithmBitboards\communication-files\cppTOpy_communication.txt)";
    constexpr static char PY_TO_CPP_FILE[] = R"(D:\Dokumenty\_skola\DlouhodobaMaturitniPrace\ChessBoardProgram\ChessAlgorithmBitboards\communication-files\pyTOcpp_communication.txt)";
};


#endif //CHESSALGORITHMBITBOARDS_BOARDUI_H
