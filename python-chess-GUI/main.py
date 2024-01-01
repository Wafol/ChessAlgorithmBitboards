from typing import Union
from pygame import Surface, SurfaceType
import pygame
from piece_textures import PieceTextures
from chess_board import ChessBoard

FEN = 'rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR'


class App:
    def __init__(self):
        self._chess_board: ChessBoard = None
        self._piece_textures = None
        self._running = True
        self._screen = None
        self._size = self._width, self._height = 536, 536

    def on_init(self):
        pygame.init()
        self._screen = pygame.display.set_mode(self._size)

        self._piece_textures = PieceTextures("res/pieces.png", self._width//8)
        self._chess_board = ChessBoard(self._screen, self._piece_textures, self._size)

        self._running = True

    def on_event(self, event):
        if event.type == pygame.QUIT:
            self._running = False

        if event.type == pygame.MOUSEBUTTONUP:
            pos = pygame.mouse.get_pos()
            chess_coords = (pos[1]//(self._width//8), pos[0]//(self._width//8))

            self._chess_board.select_square(chess_coords)

    def on_loop(self):
        self._screen.fill((255, 255, 255))

        #### COMMUNICATION ####
        fen = self._chess_board.get_data_from_cpp()
        self._chess_board.update_pieces_arr_by_fen(fen)
        #######################

        self._chess_board.draw_board()

    def on_render(self):
        pygame.display.flip()

    def on_cleanup(self):
        pygame.quit()

    def on_execute(self):
        if self.on_init() == False:
            self._running = False

        while self._running:
            for event in pygame.event.get():
                self.on_event(event)

            self.on_loop()
            self.on_render()
        self.on_cleanup()


if __name__ == "__main__":
    theApp = App()
    theApp.on_execute()
