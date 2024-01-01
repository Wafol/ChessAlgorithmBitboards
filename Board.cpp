#include "Board.h"
#include <cstring>
#include <unordered_map>

Board::Board() {
    memset(bitboards, 0, sizeof(bitboards));
    memset(castling, 0, sizeof(castling));

    char board[8][8] = {
            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    arrayToBitboards(board);
}

std::string Board::getFENBoard() {
    char board[8][8];
    bitboardsToArray(board, bitboards);

    std::string fen;

    int space = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == ' ' || board[i][j] == '.') {
                space++;
            } else {
                if (space > 0) {
                    fen += std::to_string(space);
                    space = 0;
                }

                fen += board[i][j];
            }
        }

        if (space > 0) {
            fen += std::to_string(space);
            space = 0;
        }

        if (i != 7)
            fen += "/";
    }

    return fen;
}

void Board::movePiece(OneMove move) {
    char board[8][8];
    bitboardsToArray(board, bitboards);

    char mem = board[move.i1][move.j1];
    board[move.i1][move.j1] = ' ';
    board[move.i2][move.j2] = mem;

    arrayToBitboards(board);
}

void Board::arrayToBitboards(char (&src_board)[8][8]) {
    memset(bitboards, 0, sizeof(bitboards));

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            uint64_t bin_piece_pos = 1ULL<<(j + i*8);
            PieceType piece_i = charToPieceEnum(src_board[i][j]);
            if (piece_i == NONE) continue;

            bitboards[piece_i] |= bin_piece_pos;
        }
    }
}

void Board::bitboardsToArray(char (&dest_board)[8][8], uint64_t (&bitboards)[12]) {
    for (int i = 0; i < 64; i++) {
        dest_board[i/8][i%8] = '.';

        for (int j = 0; j < 12; j++) {
            if ((bitboards[j]&(1ULL<<i)) != 0) {
                char char_piece = pieceEnumToChar(static_cast<PieceType>(j));
                dest_board[i/8][i%8] = char_piece;
                break;
            }
        }
    }
}


PieceType Board::charToPieceEnum(char char_piece){
    static const std::unordered_map<char, PieceType> char_to_piece_map = {
            {'P', P}, {'R', R}, {'N', N}, {'B', B}, {'Q', Q}, {'K', K},
            {'p', p}, {'r', r}, {'n', n}, {'b', b}, {'q', q}, {'k', k}
    };

    auto it = char_to_piece_map.find(char_piece);
    return (it != char_to_piece_map.end()) ? it->second : NONE;
}

char Board::pieceEnumToChar(PieceType piece_type) {
    static const std::unordered_map<PieceType, char> piece_to_char_map = {
            {P, 'P'}, {R, 'R'}, {N, 'N'}, {B, 'B'}, {Q, 'Q'}, {K, 'K'},
            {p, 'p'}, {r, 'r'}, {n, 'n'}, {b, 'b'}, {q, 'q'}, {k, 'k'},
            {NONE, '.'}
    };

    auto it = piece_to_char_map.find(piece_type);
    return (it != piece_to_char_map.end()) ? it->second : '.';
}



