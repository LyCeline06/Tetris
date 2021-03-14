#ifndef BOARDAI_H
#define BOARDAI_H
#include <iostream>
#include <cmath>

#include <SDL.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Piece.h"
#include "Board_AI.h"


const int WIDTH_AI= 10; //game
const int HEIGHT_AI= 20; //game and window
const int WIDTH_W_AI= 40; //window

enum  {LEFT_AI, RIGHT_AI, UP_AI, DOWN_AI};


class Board_ai{
    Piece curPiece_ai;

public:
	SDL_Color board_ai[HEIGHT_AI][WIDTH_AI];

    Board_ai();
	
	Piece getcurPiece_ai() ;
	void setcurPiece_ai(Piece p);
	bool update_ai(int, SDL_Renderer* renderer, int*);
	int line_ai();
	void gravity_ai(int i);
	bool fit_ai(Piece p);
	void rotate2_ai();
	bool absorb_ai();
	void draw_board_ai(SDL_Renderer* renderer, int border);
	void gravity_piece_ai(SDL_Renderer* renderer, int*);
};




#endif
