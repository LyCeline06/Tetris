#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <cmath>

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Piece.h"

const int WIDTH=10;
const int HEIGHT=10;
enum  {LEFT, RIGHT, UP, DOWN};


class Board{
    Piece curPiece;

public:
	SDL_Color board[HEIGHT][WIDTH];
    Board();
	Piece getcurPiece() ;
	void setcurPiece(Piece p);
	void update(int, SDL_Renderer* renderer);
	int line();
	void gravity(int i);
	bool fit(Piece p);
	void rotate2();
	void absorb();
	void draw_board(SDL_Renderer* renderer);
	void gravity_piece(SDL_Renderer* renderer);
};




#endif
