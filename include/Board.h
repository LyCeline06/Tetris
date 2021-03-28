#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <cmath>

#include <SDL.h>
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Piece.h"
using namespace std;
const int WIDTH = 10; //game
const int HEIGHT = 20; //game and window
const int WIDTH_W = 40; //window

enum  {LEFT, RIGHT, UP, DOWN};

typedef array<SDL_Color, WIDTH> row_type;
typedef array<row_type, HEIGHT> array_type;

class Board{
    Piece curPiece;
	array_type board;
public:
    Board();
	const array_type& get_Board() const {return board;}
	Piece getcurPiece() ;
	void setcurPiece(Piece p);
	bool update(int, SDL_Renderer* renderer, pair<int,int>*);
	int line();
	void gravity(int i);
	bool fit(Piece p);
	void rotate2();
	bool absorb();
	void draw_board(SDL_Renderer* renderer, int border);
	void gravity_piece(SDL_Renderer* renderer, pair<int,int>*);
};




#endif
