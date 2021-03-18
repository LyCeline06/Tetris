#ifndef PIECE_H_
#define PIECE_H_
#include <SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>

#include "Shape.h"

static const int tile_size = 22;

class Piece {
	Shape s;
	int x, y;  // x,y correspondent a en haut a gauche de la pièce
   public:
	int getX();
	int getY();
	void setX(int x2);
	void setY(int y2);
	Shape getShape();
	void setShape(Shape sh);
	Piece();
	Piece(Shape s2, int x2, int y2);
	void draw_piece(SDL_Renderer* renderer);
	int wid();
	int hei();
	int Real_x();
};

#endif
