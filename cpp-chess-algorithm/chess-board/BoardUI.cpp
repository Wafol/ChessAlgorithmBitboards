#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include "BoardUI.h"
#include "Board.h"

void BoardUI::initCommunication() {
    std::fstream file_delete(CPP_TO_PY_FILE, std::ios::out);
    std::fstream file_delete2(PY_TO_CPP_FILE, std::ios::out);
}

bool BoardUI::handlePlayerMove(std::string move_input, Board &board) {
    std::transform(move_input.begin(), move_input.end(), move_input.begin(), ::tolower);
    std::vector<char> file_names = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    auto file1_it = std::find(file_names.begin(), file_names.end(), move_input.at(0));
    auto file2_it = std::find(file_names.begin(), file_names.end(), move_input.at(2));

    if (move_input.size() != 4
        || file1_it == file_names.end()
        || (move_input.at(1) - '0') < 1 || (move_input.at(1) - '0') > 8
        || file2_it == file_names.end()
        || (move_input.at(3) - '0') < 1 || (move_input.at(3) - '0') > 8)
        return false;

    OneMove player_move;
    player_move.i1 = 8 - (move_input.at(1) - '0');
    player_move.j1 = std::distance(file_names.begin(), file1_it);;
    player_move.i2 = 8 - (move_input.at(3) - '0');
    player_move.j2 = std::distance(file_names.begin(), file2_it);;

    board.movePiece(player_move);

    return true;
}

void BoardUI::writeInfoToCommunicationFile(Board &board) {
    std::ifstream in_file;
    in_file.open(CPP_TO_PY_FILE);

    std::string content;
    in_file >> content;
    in_file.close();

    if (content == board.getFENBoard())
        return;

    /////////////////////////
    std::ofstream file;
    file.open(CPP_TO_PY_FILE);

    file << board.getFENBoard();
    if (board.on_turn == WHITE)
        file << " w\n";
    else if (board.on_turn == BLACK)
        file << " b\n";

    for (OneMove move : board.possible_moves) {
        file << move.toString() << "\n";
    }

    file.close();
}

OneMove BoardUI::getMoveFromPython(Board &board) {
    OneMove move;
    move.valid = false;

    std::ifstream file;
    file.open(PY_TO_CPP_FILE);

    std::string content;
    file >> content;

    if (!content.empty()) {
        move.i1 = content[0] - '0';
        move.j1 = content[1] - '0';
        move.i2 = content[2] - '0';
        move.j2 = content[3] - '0';
        move.valid = true;

        std::fstream file_delete(PY_TO_CPP_FILE, std::ios::out);
        file.close();

        return move;
    }

    file.close();
    return move;
}

void BoardUI::drawBoard(char (&board)[8][8], bool show_indexes) {
    if (show_indexes)
        std::cout << "    0 1 2 3 4 5 6 7" << std::endl << std::endl;
    else
        std::cout << "    A B C D E F G H" << std::endl << std::endl;


    for (int i = 0; i < 8; i++) {
        if (show_indexes)
            std::cout << i << "   ";
        else
            std::cout << 8 - i << "   ";

        for (int j = 0; j < 8; j++) {
            char c = board[i][j];
            if (c == ' ') c = '.';

            std::cout << c;

            if (j < 7)
                std::cout << ' ';
        }

        std::cout << std::endl;
    }
}

void BoardUI::drawBitboards(uint64_t (&bitboards)[12], bool show_indexes) {
    char board[8][8];
    Board::bitboardsToArray(board, bitboards);
    drawBoard(board, show_indexes);
}

void BoardUI::printMoves(std::vector<OneMove> moves) {
    for (OneMove move : moves) {
        std::cout << static_cast<int>(move.i1) << " " << static_cast<int>(move.j1) << "  "
        << static_cast<int>(move.i2) << " " << static_cast<int>(move.j2) << "  Promotion: " << move.promotion << std::endl;
    }
}

void BoardUI::drawBitboard(uint64_t bitboard) {
    uint64_t bitboards[12];
    memset(bitboards, 0, sizeof(bitboards));
    bitboards[0] = bitboard;

    drawBitboards(bitboards, true);
}







