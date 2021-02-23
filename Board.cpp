#include"Board.h"
#include <iostream>
#include <cmath>


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Board::Board() : curPiece()
{
	for(int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++)
			board[i][j] = black;
		}
}


Piece Board::getcurPiece(){
	return curPiece;
}

void Board::setcurPiece(Piece p){
	curPiece=p;
}

void Board::gravity(int i){
    for (int k=0;k<i;k++)
        for (int j=0;j<HEIGHT;j++)
             board[i+1][j]=board[i][j];

    for (int j=0;j<HEIGHT;j++)
        board[0][j]=black;
}

int Board::line(){
    bool res=true;

    for (int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT;j++)
            if (board[i][j].g==0)
                res=false;
        if (res)
            return i;
    }

	return -1;
}

void Board::update(int move,SDL_Renderer* renderer)
{										//0 left, 1 right, 2 up, 3 down
	int x = curPiece.getX();
	int y = curPiece.getY();
	Shape s = curPiece.getShape();

	if (move == LEFT && x-1 >=0)
		curPiece.setX(x - 1);

    if (move == RIGHT){
		bool b = true;
		for (int i = 0 ; i < s.size ; i++)
			for (int j = 0 ; j < s.size ; j++)
				if (s.matrix[i][j])
				{
					printf("%i\n", x+j+1);
					if (x+j+1 == WIDTH )
						b = false;
					else if (board[i+y][j+x+1].g!=0)
						b = false;
				}
		if (b)
			curPiece.setX(x + 1);
	}

	if (move == DOWN){
	 	bool b = true;
		for (int i = 0 ; i < s.size ; i++)
			for (int j = 0 ; j < s.size ; j++)
				if (s.matrix[i][j])
				{
					printf("%i\n", i+y+1);
					if (i+y+1 == HEIGHT)
						b = false;
					else if (board[i+y+1][j+x].g!=0)
						b = false;
				}
		if (b)
			curPiece.setY(y + 1);
	}

    if (move == UP)
		rotate2();
	absorb();
	draw_board(renderer);
}

bool Board::fit(Piece p){
	Shape s=p.getShape();
	int x = p.getX();
	int y = p.getY();
	bool res=true;
	for (int i=0;i<s.size;i++)
		for (int j=0;j<s.size;j++)
			if (s.matrix[i][j] ){
				if (i+y<HEIGHT && i+y>=0 && x+j<WIDTH && x+j>=0){
					if (board[i+y][j+x].g!=0)
						res = false;}
				else res=false;}
	return res;
}

void Board::rotate2(){
	Shape s=curPiece.getShape();
	Shape s2 =rotate(s);
	int x=curPiece.getX();
	int y=curPiece.getY();
	Piece p = {s2,x,y};
	bool b = fit(p);
	if (b)
		curPiece.setShape(s2);
}

void Board::draw_board(SDL_Renderer* renderer){
	SDL_Rect rect;
	rect.w=tile_size*10;
	rect.h=tile_size*10;

	for (int x=0;x<WIDTH;x++)
		for (int y=0;y<HEIGHT;y++){
			SDL_SetRenderDrawColor(renderer,board[y][x].r,board[y][x].g,board[y][x].b,255);
			rect.x=x*tile_size;
			rect.y=y*tile_size;
			SDL_RenderFillRect(renderer,&rect);
		}

}
void Board::absorb(){
    int x=curPiece.getX();
    int y=curPiece.getY();
    Shape s=curPiece.getShape();
    bool b=false;
    for (int i=0;i<s.size;i++)
        for (int j=0;j<s.size;j++)
            if (s.matrix[i][j]){
                if (i+y+1<HEIGHT)
                {
                    if (board[i+y+1][j+x].g!=0)
                        b=true;
				}
                else
                    b=true;
            }
    if (b){
        for (int i=0;i<s.size;i++)
            for (int j=0;j<s.size;j++){
                board[i+y][j+x].r=s.color.r;
				board[i+y][j+x].g=s.color.g;
				board[i+y][j+x].b=s.color.b;}
        Piece p;
        curPiece=p;
    }
}
