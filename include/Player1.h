#ifndef PLAYER1_H
#define PLAYER1_H

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

#include "Stat.h"
#include "Board.h"
#include "Piece.h"
#include "Shape.h"
#include "Player.h"

class Ia;
class Multi;

class Player1 : protected Player
{
	public :
		Player1();

		bool input(const Uint8 *keys, SDL_Renderer* renderer, bool *running);

		void render(SDL_Renderer* renderer, int frameCount, int lastFrame);

		void play(SDL_Renderer* renderer, bool running, bool end_b,
			SDL_Texture* gameover, int frameCount, int timerFPS, int lastFrame,
			int fps, SDL_Window* window);

		friend class Ia;
		friend class Multi;
};

#endif
