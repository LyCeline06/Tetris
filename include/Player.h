#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <cmath>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Shape.h"
#include "Stat.h"

using namespace std;

class Player {
   protected:
	Board* board;
	pair<int, int> correct_line;  // first : accumulator of second ; second : nb
								  // of correct lines not disappeared yet
	int level_;
	float speed;

   public:
	Player();
	Board* get_board();
	pair<int, int> get_correct_line();
	void create_finalimage(int player, SDL_Texture* img,
						   SDL_Renderer* renderer);
};

#endif
