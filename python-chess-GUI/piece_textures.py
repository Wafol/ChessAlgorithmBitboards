from typing import List
import pygame

class PieceTextures:
    def __init__(self, pieces_image_path: str, square_size: int):
        pieces_image = pygame.image.load(pieces_image_path).convert_alpha()

        self.square_size = square_size

        im_width = pieces_image.get_rect().width
        im_height = pieces_image.get_rect().height
        im_rows = 6
        im_col = 2

        # sorted as in image
        piece_types = ['K', 'Q', 'B', 'N', 'R', 'P', 'k', 'q', 'b', 'n', 'r', 'p']
        self.pieces_dict = {}

        for i in range(im_col):
            for j in range(im_rows):
                piece_image = pieces_image.subsurface([im_width//im_rows*j, im_height//im_col*i, im_width//im_rows, im_height//im_col])
                piece_image = pygame.transform.scale(piece_image, (square_size, square_size))

                self.pieces_dict[piece_types[i*6 + j]] = piece_image

    def draw_piece(self, screen, piece_type: str, position: List[int]):
        piece_image = self.pieces_dict[piece_type]
        screen.blit(piece_image, (position[1]*self.square_size, position[0]*self.square_size))
