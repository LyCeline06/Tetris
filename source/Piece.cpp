#include "../include/Piece.h"
#include "../include/Board.h"


Piece::Piece()
{
	int val=rand()%7;
	x=WIDTH/2-1;
	y=0;
	s = block[val];
}

Piece::Piece(Shape s2, int x2, int y2){
	s=s2;
	x=x2;
	y=y2;
}

int Piece::getX(){
	return x;
}

int Piece::getY(){
	return y;
}

void Piece::setX(int x2){
	x=x2;
}


void Piece::setY(int y2){
	y=y2;
}

Shape Piece::getShape(){
	return s;
}


void Piece::setShape(Shape sh){
	s = sh;
}

void Piece::draw_piece(SDL_Renderer* renderer){
	SDL_Rect rect;
	rect.w=tile_size;
	rect.h=tile_size;

	Shape s = this->getShape();

	for (int i=0;i<s.size;i++)
		for (int j=0;j<s.size;j++)
			if(s.matrix[i][j]==1){
				rect.x=(j+x)*tile_size;
				rect.y=(i+y)*tile_size;
                SDL_SetRenderDrawColor(renderer, s.color.r, s.color.g, s.color.b, 255);
                SDL_RenderFillRect(renderer, &rect);
			}
}
