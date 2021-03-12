#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <cmath>

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Piece.h"

const int WIDTH = 10; //game
const int HEIGHT = 20; //game and window
const int WIDTH_W = 40; //window

enum  {LEFT, RIGHT, UP, DOWN};


class Board{
    Piece curPiece;

public:
	SDL_Color board[HEIGHT][WIDTH];
    Board();
	Piece getcurPiece() ;
	void setcurPiece(Piece p);
	bool update(int, SDL_Renderer* renderer, int*);
	int line();
	void gravity(int i);
	bool fit(Piece p);
	void rotate2();
	bool absorb();
	void draw_board(SDL_Renderer* renderer, int border);
	void gravity_piece(SDL_Renderer* renderer, int*);
};




#endif
