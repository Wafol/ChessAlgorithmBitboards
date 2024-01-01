from typing import List
import pygame

class PieceTextures:
    def __init__(self, pieces_image_path: str, square_size: int):
        self.square_size = square_size

        self.pieces_dict = {
            'K': pygame.transform.scale(pygame.image.load('res/wk.png').convert_alpha(), (square_size, square_size)),
            'Q': pygame.transform.scale(pygame.image.load('res/wq.png').convert_alpha(), (square_size, square_size)),
            'B': pygame.transform.scale(pygame.image.load('res/wb.png').convert_alpha(), (square_size, square_size)),
            'N': pygame.transform.scale(pygame.image.load('res/wn.png').convert_alpha(), (square_size, square_size)),
            'R': pygame.transform.scale(pygame.image.load('res/wr.png').convert_alpha(), (square_size, square_size)),
            'P': pygame.transform.scale(pygame.image.load('res/wp.png').convert_alpha(), (square_size, square_size)),
            'k': pygame.transform.scale(pygame.image.load('res/bk.png').convert_alpha(), (square_size, square_size)),
            'q': pygame.transform.scale(pygame.image.load('res/bq.png').convert_alpha(), (square_size, square_size)),
            'b': pygame.transform.scale(pygame.image.load('res/bb.png').convert_alpha(), (square_size, square_size)),
            'n': pygame.transform.scale(pygame.image.load('res/bn.png').convert_alpha(), (square_size, square_size)),
            'r': pygame.transform.scale(pygame.image.load('res/br.png').convert_alpha(), (square_size, square_size)),
            'p': pygame.transform.scale(pygame.image.load('res/bp.png').convert_alpha(), (square_size, square_size))
        }

        ''' CODE FOR PIECES.PNG
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
        '''

    def draw_piece(self, screen, piece_type: str, position: List[int]):
        piece_image = self.pieces_dict[piece_type]
        screen.blit(piece_image, (position[1]*self.square_size, position[0]*self.square_size))
