import pygame
from piece_textures import PieceTextures
from typing import List, Tuple

class ChessBoard:
    def __init__(self, screen, piece_textures: PieceTextures, scree_size: (int, int)):
        self._screen = screen
        self._piece_textures = piece_textures
        self._square_size = scree_size[0]//8

        self._highlighted_rects = ()
        self.COMMUNICATION_FILE_PATH = "D:\Dokumenty\_skola\DlouhodobaMaturitniPrace\ChessBoardProgram\ChessAlgorithmBitboards\communication-files\cppTOpy_communication.txt"

        self._fen = ''
        self._poss_moves = ()

        self._selected_square = ()

    def get_data_from_cpp(self):
        f = open(self.COMMUNICATION_FILE_PATH, "r")

        # 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR'
        line = f.readline()
        self._fen = line.replace('\n', '')

        self._poss_moves = ()

        while line:
            line = f.readline().replace('\n', '')

            if len(line) == 4:
                move = (int(line[0]), int(line[1]), int(line[2]), int(line[3]))
                self._poss_moves = self._poss_moves + (move,)

    def draw_board(self):
        self.draw_board_background()
        self.draw_possible_moves()

        self.draw_by_fen(self._fen)

    def draw_board_background(self):
        for i in range(8):
            for j in range(8):
                if (i + j) % 2 == 0:
                    color = (0xEE, 0xEE, 0xD2)
                else:
                    color = (0x76, 0x96, 0x56)

                pygame.draw.rect(self._screen, color, (j*self._square_size, i*self._square_size, self._square_size, self._square_size))

    def draw_by_fen(self, fen: str):
        fen = fen.split('/')

        i = 0
        for row in fen:
            j = 0

            for c in row:
                if c.isnumeric():
                    j += int(c)
                else:
                    self._piece_textures.draw_piece(self._screen, c, [i, j])
                    j += 1

            i += 1

    def select_square(self, coords: (int, int)):
        self._selected_square = coords

    def draw_possible_moves(self):
        if len(self._selected_square) == 0:
            return

        for move in self._poss_moves:
            if move[0] == self._selected_square[0] and move[1] == self._selected_square[1]:
                pygame.draw.rect(self._screen, (0, 255, 0), (move[3]*self._square_size, move[2]*self._square_size, self._square_size, self._square_size))

    def update_highlighted_rects(self, rects):
        self._highlighted_rects = rects

    def highlight_rects(self):
        for rect in self._highlighted_rects:
            pygame.draw.rect(self._screen, (0, 0, 255), (rect[0]*self._square_size, rect[1]*self._square_size, self._square_size, self._square_size))
