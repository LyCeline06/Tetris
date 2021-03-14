#ifndef STAT_H
#define STAT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include "Board.h"
#include "Piece.h"
#include <iostream>
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


class Stat
{
	TTF_Font * font;
	SDL_Rect rect1, rect2;
	SDL_Texture * texture1;
	SDL_Texture * texture2;
	char msg[1000000];
	int stat;
	int nb;							//threshold to separate the different stats
	int score_base;
	int priority;
	SDL_Renderer* renderer;
	int ai; //if ai , ai=1

	public :
		Stat() = default;
		Stat(char *msg1, int nb, int score_base, int priority, SDL_Renderer* renderer,int ai=0);

		void get_text_and_rect(SDL_Renderer * renderer, int x, int y, char * text,
		TTF_Font * font, SDL_Texture ** texture, SDL_Rect * rect);

		void render_stat(int*);

		void set_stat(int new_stat);

		~Stat();
};
#endif
