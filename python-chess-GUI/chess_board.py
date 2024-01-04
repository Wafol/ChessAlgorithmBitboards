import pygame
from piece_textures import PieceTextures
from typing import List, Tuple

class ChessBoard:
    def __init__(self, screen, piece_textures: PieceTextures, scree_size: (int, int)):
        self._screen = screen
        self._piece_textures = piece_textures
        self._square_size = scree_size[0]//8

        self._highlighted_rects = ()
        self.CPP_TO_PY_FILE = "D:\Dokumenty\_skola\DlouhodobaMaturitniPrace\ChessBoardProgram\ChessAlgorithmBitboards\communication-files\cppTOpy_communication.txt"
        self.PY_TO_CPP_FILE = "D:\Dokumenty\_skola\DlouhodobaMaturitniPrace\ChessBoardProgram\ChessAlgorithmBitboards\communication-files\pyTOcpp_communication.txt"

        self._pieces_arr = ()  # 8x8 char array, with pieces KQP... and blank spots ' '
        self._fen = ''
        self._poss_moves = ()  # unordered tuple of tuples ((1,2,2,3), ...)
        self._on_turn = ''

        self._selected_square = ()

    def get_data_from_cpp(self) -> str:
        f = open(self.CPP_TO_PY_FILE, "r")

        # 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w'
        line = f.readline()
        self._fen = line.replace('\n', '')
        self.update_board_by_fen(self._fen)

        # generate possible moves
        if len(self._fen.split()) < 2:
            print('\n\nWRONG FEN FORMAT SEND\n\n')
            print(self._fen)
            return

        self._on_turn = self._fen.split(' ')[1]
        self._poss_moves = ()

        while line:
            line = f.readline().replace('\n', '')

            if len(line) == 4:
                move = (int(line[0]), int(line[1]), int(line[2]), int(line[3]))

                if (self._pieces_arr[move[0]][move[1]].isupper() and self._on_turn == 'w') or (self._pieces_arr[move[0]][move[1]].islower() and self._on_turn == 'b'):
                    self._poss_moves = self._poss_moves + (move,)

        return self._fen

    def send_move_to_cpp(self, move: (int, int, int, int)):
        f = open(self.PY_TO_CPP_FILE, "w")
        f.write(str(move[0]) + str(move[1]) + str(move[2]) + str(move[3]))

    def piece_arr_to_fen(self):
        fen = ''
        space = 0

        for i in range(8):
            for j in range(8):
                if self._pieces_arr[i][j] == ' ' or self._pieces_arr[i][j] == '.':
                    space += 1
                else:
                    if space > 0:
                        fen += str(space)
                        space = 0

                    fen += self._pieces_arr[i][j]

            if space > 0:
                fen += str(space)
                space = 0

            if i != 7:
                fen += '/'

        return fen

    def draw_board(self):
        self.draw_board_background()
        self.highlight_selected_square()

        self.draw_pieces()
        self.draw_possible_moves()

    def draw_board_background(self):
        for i in range(8):
            for j in range(8):
                if (i + j) % 2 == 0:
                    color = (0xEE, 0xEE, 0xD2)
                else:
                    color = (0x76, 0x96, 0x56)

                pygame.draw.rect(self._screen, color, (j*self._square_size, i*self._square_size, self._square_size, self._square_size))

    def update_board_by_fen(self, fen: str):
        # update the board
        self._pieces_arr = [[' ' for _ in range(8)] for _ in range(8)]
        fen = fen.split('/')

        i = 0
        for row in fen:
            j = 0

            for c in row:
                if c == ' ':
                    return

                if c.isnumeric():
                    j += int(c)
                else:
                    self._pieces_arr[i][j] = c
                    j += 1

            i += 1

    def draw_pieces(self):
        for i in range(8):
            for j in range(8):
                if self._pieces_arr[i][j] != ' ' and self._pieces_arr[i][j] != '.':
                    self._piece_textures.draw_piece(self._screen, self._pieces_arr[i][j], [i, j])

    def select_square(self, coords: (int, int)):
        if len(self._selected_square) > 0:
            for move in self._poss_moves:
                if (move[0] == self._selected_square[0] and move[1] == self._selected_square[1]) and (move[2] == coords[0] and move[3] == coords[1]):
                    self.send_move_to_cpp(move)
                    self._selected_square = ()
                    return

        self._selected_square = coords

    def draw_possible_moves(self):
        if len(self._selected_square) == 0:
            return

        for move in self._poss_moves:
            if move[0] == self._selected_square[0] and move[1] == self._selected_square[1]:
                # pygame.draw.rect(self._screen, (0, 255, 0), (move[3]*self._square_size, move[2]*self._square_size, self._square_size, self._square_size))
                pygame.draw.circle(self._screen, (240, 88, 77), (move[3]*self._square_size + self._square_size/2, move[2]*self._square_size + self._square_size/2), self._square_size//4)

    def highlight_selected_square(self):
        if len(self._selected_square) == 0:
            return

        pygame.draw.rect(self._screen, (0, 255, 0), (self._selected_square[1]*self._square_size, self._selected_square[0]*self._square_size, self._square_size, self._square_size))

    def update_highlighted_rects(self, rects):
        self._highlighted_rects = rects

    def highlight_rects(self):
        for rect in self._highlighted_rects:
            pygame.draw.rect(self._screen, (0, 0, 255), (rect[0]*self._square_size, rect[1]*self._square_size, self._square_size, self._square_size))
