#include "../include/Board_AI.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>


int notempty_ai(SDL_Color color){
	if (color.g != 25) return 1;
	return 0;
}
// black board_ai
Board_ai::Board_ai() : curPiece_ai() {
	for (int i = 0; i < HEIGHT_AI; i++) {
		for (int j = 0; j < WIDTH_AI; j++)
		board_ai[i][j] = grey;
	}
}	

Piece Board_ai::getcurPiece_ai() { return curPiece_ai; }

void Board_ai::setcurPiece_ai(Piece p) { curPiece_ai = p; }

void Board_ai::gravity_ai(int i) {
	if (i >= 0) {
		for (int k = i; k >= 0; k--)
			for (int j = 0; j < WIDTH_AI; j++) {
				board_ai[k][j] = board_ai[k - 1][j];
			}
		for (int j = 0; j < WIDTH_AI; j++) {
			board_ai[0][j] = grey;
		}
	}
	return;
}

// looks for a completed line
int Board_ai::line_ai() {
	for (int i = 0; i < HEIGHT_AI; i++) {
		bool res = true;
		for (int j = 0; j < WIDTH_AI; j++) {
			if (!notempty_ai(board_ai[i][j])) res = false;
		}
		if (res == true) return i;
	}

	return -1;
}

bool Board_ai::update_ai(int move, SDL_Renderer * renderer, int * correct_line_ai) {
	int x = curPiece_ai.getX();
	int y = curPiece_ai.getY();
	Shape s = curPiece_ai.getShape();

	if (move == LEFT_AI) {
		bool b = true;
		for (int i = 0; i < s.size; i++)
			for (int j = 0; j < s.size; j++)
				if (s.matrix[i][j]) {
					if (x + j - 1 < 0)
						b = false;
					else if (notempty_ai(board_ai[i + y][j + x - 1]))
						b = false;
				}
		if (b) curPiece_ai.setX(x - 1);
	}

	if (move == RIGHT_AI) {
		bool b = true;
		for (int i = 0; i < s.size; i++)
			for (int j = 0; j < s.size; j++)
				if (s.matrix[i][j]) {
					if (x + j + 1 == WIDTH_AI)
						b = false;
					else if (notempty_ai(board_ai[i + y][j + x + 1]))
						b = false;
				}
		if (b) curPiece_ai.setX(x + 1);
	}

	if (move == DOWN_AI) {
		bool b = true;
		for (int i = 0; i < s.size; i++)
			for (int j = 0; j < s.size; j++)
				if (s.matrix[i][j]) {
					if (i + y + 1 == HEIGHT_AI)
						b = false;
					else if (notempty_ai(board_ai[i + y + 1][j + x]))
						b = false;
				}
		if (b) curPiece_ai.setY(y + 1);
	}

	if (move == UP_AI) {
		rotate2_ai();
	}

    bool b2 = absorb_ai();
    while (line_ai() != -1) {
		printf("oui\n");
        gravity_ai(line_ai());
        (* correct_line_ai) ++;
    }
    return b2;
}

bool Board_ai::fit_ai(Piece p) {
	Shape s = p.getShape();
	int x = p.getX();
	int y = p.getY();
	bool res = true;
	for (int i = 0; i < s.size; i++)
		for (int j = 0; j < s.size; j++)
			if (s.matrix[i][j]) {
				if (i + y < HEIGHT_AI && i + y >= 0 && x + j < WIDTH_AI &&
					x + j >= 0) {
					if (notempty_ai(board_ai[i + y][j + x])) res = false;
				} else
					res = false;
			}
	return res;
}

void Board_ai::rotate2_ai() {
	Shape s = curPiece_ai.getShape();
	Shape s2 = rotate(s);
	int x = curPiece_ai.getX();
	int y = curPiece_ai.getY();
	Piece p = {s2, x, y};
	bool b = fit_ai(p);
	if (b) curPiece_ai.setShape(s2);
}

void Board_ai::draw_board_ai(SDL_Renderer* renderer, int border) {
	SDL_Rect rect;
	rect.w = tile_size - border;
	rect.h = tile_size - border;

	for (int x = 0; x < WIDTH_AI; x++)
		for (int y = 0; y < HEIGHT_AI; y++) {
			SDL_SetRenderDrawColor(renderer, board_ai[y][x].r, board_ai[y][x].g,
								   board_ai[y][x].b, 255);
			rect.x = WIDTH_AI*2*tile_size + x * tile_size + border;
			rect.y = y * tile_size + border;
			SDL_RenderFillRect(renderer, &rect);
		}
}
// absorb and replace in collision
bool Board_ai::absorb_ai() {
	int x = curPiece_ai.getX();
	int y = curPiece_ai.getY();
	Shape s = curPiece_ai.getShape();
	bool b = false;
	for (int i = 0; i < s.size; i++)
		for (int j = 0; j < s.size; j++)
			if (s.matrix[i][j]) {
				if (i + y + 1 < HEIGHT_AI) {
					if (notempty_ai(board_ai[i + y + 1][j + x])) b = true;
				} else
					b = true;
			}
	if (b) {
		SDL_Delay(50);
		for (int i = 0; i < s.size; i++)
			for (int j = 0; j < s.size; j++)
				if (s.matrix[i][j]) {
					board_ai[i + y][j + x] = s.color;
				}
		Piece p;
		curPiece_ai = p;

		if (!fit_ai(p)) return false;
	}
	return true;
}

void Board_ai::gravity_piece_ai(SDL_Renderer * renderer, int * correct_line_ai) {
    update_ai(DOWN_AI, renderer, correct_line_ai);
}
