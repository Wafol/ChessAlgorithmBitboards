#include "Board.h"
#include "MovesGeneration.h"
#include <iostream>
#include <cstring>
#include <unordered_map>

Board::Board() {
    memset(bitboards, 0, sizeof(bitboards));
    memset(castling, true, sizeof(castling));

    char board[8][8] = {
            {'r', 'n', 'b', ' ', 'k', ' ', ' ', ' '},
            {'p', 'p', 'p', ' ', ' ', ' ', ' ', 'p'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
            {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

    arrayToBitboards(board);

    on_turn = WHITE;
    game_over = false;

    MovesGeneration moves_gener;
    possible_moves = moves_gener.generatePossibleMoves(*this, BOTH);
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
    if (game_over)
        return;

    if (!makeCastlingMove(bitboards, move))
        makeMoveInBitboards(move, bitboards);

    /*char board[8][8];
    bitboardsToArray(board, bitboards);

    if (!handleCastling(board, move)) {
        char mem = board[move.i1][move.j1];
        board[move.i1][move.j1] = ' ';
        board[move.i2][move.j2] = mem;
    }

    arrayToBitboards(board);*/

    //CHECK control
    MovesGeneration moves_gener;
    std::vector<OneMove> possible_white_moves =  moves_gener.generatePossibleMoves(*this, WHITE);
    std::vector<OneMove> possible_black_moves =  moves_gener.generatePossibleMoves(*this, BLACK);
    game_over = (possible_white_moves.empty() || possible_black_moves.empty());

    possible_moves = {};
    possible_moves.insert(possible_moves.end(), possible_white_moves.begin(), possible_white_moves.end());
    possible_moves.insert(possible_moves.end(), possible_black_moves.begin(), possible_black_moves.end());

    on_turn = static_cast<PlayerType>(!on_turn); //switch current player
}

PieceType Board::makeMoveInBitboards(OneMove move, uint64_t (&bitboards)[12]) {
    PieceType moved_piece = NONE;

    for (int i = 0; i < 12; i++) {
        if (((1ULL << (move.j2 + move.i2*8)) & bitboards[i]) != 0) { //if opponent is on destination square (=> erase it)
            bitboards[i] &= ~(1ULL << (move.j2 + move.i2*8));
        }

        if (((1ULL << (move.j1 + move.i1*8)) & bitboards[i]) != 0) { //if move is from i bitboard
            bitboards[i] &= ~(1ULL << (move.j1 + move.i1*8));
            bitboards[i] |= (1ULL << (move.j2 + move.i2*8));

            moved_piece = static_cast<PieceType>(i);
        }
    }

    return moved_piece;
}

bool Board::makeCastlingMove(uint64_t (&bitboards)[12], OneMove move) {
    PieceType piece_to_move = NONE;// = board[move.i1][move.j1];

    uint64_t start_bitboard = 1ULL << (move.j1 + move.i1*8);
    //uint64_t dest_bitboard = 1ULL << (move.j2 + move.i2*8);

    for (int i = 0; i < 12; i++) {
        if ((start_bitboard & bitboards[i]) != 0) { //if move is from i bitboard
            piece_to_move = static_cast<PieceType>(i);
            break;
        }
    }

    updateCastlingBoolsAfterMove(piece_to_move, move);

    if (piece_to_move != K && piece_to_move != k)
        return false;

    bool castling_performed = false;

    //these ifs moves the rook in castle to the right place
    if (move.i1 == 7 && move.j1 == 4 && move.i2 == 7 && move.j2 == 6) {
        bitboards[R] ^= 0b1010000000000000000000000000000000000000000000000000000000000000;
        //board[7][7] = ' ';
        //board[7][5] = 'R';

        castling_performed = true;
    } else if (move.i1 == 7 && move.j1 == 4 && move.i2 == 7 && move.j2 == 2) {
        bitboards[R] ^= 0b0000100100000000000000000000000000000000000000000000000000000000;
        //board[7][0] = ' ';
        //board[7][3] = 'R';

        castling_performed = true;
    } else if (move.i1 == 0 && move.j1 == 4 && move.i2 == 0 && move.j2 == 6) {
        bitboards[r] ^= 0b0000000000000000000000000000000000000000000000000000000010100000;
        //board[0][7] = ' ';
        //board[0][5] = 'r';

        castling_performed = true;
    } else if (move.i1 == 0 && move.j1 == 4 && move.i2 == 0 && move.j2 == 2) {
        bitboards[r] ^= 0b0000000000000000000000000000000000000000000000000000000000001001;
        //board[0][0] = ' ';
        //board[0][3] = 'r';

        castling_performed = true;
    }

    //this if moves the king to the right place
    if (castling_performed) {
        makeMoveInBitboards(move, bitboards);
    }

    return castling_performed;
}
void Board::updateCastlingBoolsAfterMove(PieceType moved_piece, OneMove move) {
    switch (moved_piece) {
        case K:
            castling[CASTLE_WK] = false;
            castling[CASTLE_WQ] = false;
            break;
        case k:
            castling[CASTLE_BK] = false;
            castling[CASTLE_BQ] = false;
            break;
        case R:
            if (move.i1 == 7 && move.j1 == 7) {
                castling[CASTLE_WK] = false;
            } else if (move.i1 == 7 && move.j1 == 0) {
                castling[CASTLE_WQ] = false;
            }
            break;
        case r:
            if (move.i1 == 0 && move.j1 == 7) {
                castling[CASTLE_BK] = false;
            } else if (move.i1 == 0 && move.j1 == 0) {
                castling[CASTLE_BQ] = false;
            }
            break;
    }
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

