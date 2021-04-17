#ifndef STAT_H
#define STAT_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <vector>

#include "Board.h"
#include "Piece.h"
using namespace std;

class Stat {
   protected:
	TTF_Font *font;
	SDL_Rect rect1, rect2;
	SDL_Texture *texture1;
	SDL_Texture *texture2;
	char msg[1000000];
	int stat;
	int nb;	 // threshold to separate the different stats
	int score_base;
	SDL_Renderer *renderer;
	int ai;	 // if ai , ai=1

   public:
	Stat() = default;
	Stat(char *msg1, int nb, int score_base, SDL_Renderer *renderer,
		 int ai = 0);

	void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
						   TTF_Font *font, SDL_Texture **texture,
						   SDL_Rect *rect);

	void set_stat(int new_stat);

	~Stat();
};

class Score : public Stat {
   public:
	Score() = default;
	Score(char *msg1, int nb, int score_base, SDL_Renderer *renderer,
		  int ai = 0);

	void render_stat(pair<int, int> *);
};

class Level : public Stat {
	vector<float> tab_speed{0.48, 0.43, 0.38, 0.33, 0.28, 0.23, 0.18, 0.13};

   public:
	Level() = default;
	Level(char *msg1, int nb, int score_base, SDL_Renderer *renderer,
		  int ai = 0);

	void render_stat(pair<int, int> *, float *speed, int *level);
};

class Lines : public Stat {
   public:
	Lines() = default;
	Lines(char *msg1, int nb, int score_base, SDL_Renderer *renderer,
		  int ai = 0);

	void render_stat(pair<int, int> *);
};

#endif
