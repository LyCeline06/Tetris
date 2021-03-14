#include "../include/Piece.h"

#include "../include/Board.h"

Piece::Piece() {
	int val = rand() % 7;
	x = WIDTH / 2 - 1;
	y = 0;
	s = block[val];
}

Piece::Piece(Shape s2, int x2, int y2) {
	s = s2;
	x = x2;
	y = y2;
}

int Piece::getX() { return x; }

int Piece::getY() { return y; }

void Piece::setX(int x2) { x = x2; }

void Piece::setY(int y2) { y = y2; }

Shape Piece::getShape() { return s; }

void Piece::setShape(Shape sh) { s = sh; }

void Piece::draw_piece(SDL_Renderer* renderer) {
	SDL_Rect rect;
	int border = 2;
	rect.w = tile_size - border;
	rect.h = tile_size - border;

	Shape s = this->getShape();

	for (int i = 0; i < s.size; i++)
		for (int j = 0; j < s.size; j++)
			if (s.matrix[i][j] == 1) {
				rect.x = (j + x) * tile_size + border;
				rect.y = (i + y) * tile_size + border;
				SDL_SetRenderDrawColor(renderer, s.color.r, s.color.g,
									   s.color.b, 255);
				SDL_RenderFillRect(renderer, &rect);
			}
}


int Piece::wid(){
	s=getShape();
	int wid=0;
	int count=0;
	for (int i=0;i<s.size;i++){
		for (int j=0;j<s.size;j++){
			if (s.matrix[i][j])
				count+=1;
		}
		if (count>wid)
			wid=count;
		count=0;
	}
	return wid;
}

int Piece::hei(){
	Shape s=getShape();
	int hei=0;
	int count=0;
	for (int j=0;j<s.size;j++){
		for (int i=0;i<s.size;i++){
			if (s.matrix[i][j])
				count+=1;
		}
		if (count>hei)
			hei=count;
		count=0;
	}
	return hei;
}

int Piece::Real_x(){
	Shape s =getShape();
	for (int j=0;j<s.size;j++)
		for (int i=0;i<s.size;i++)
			if(s.matrix[i][j])
				return j+x;
	return -1;
}
