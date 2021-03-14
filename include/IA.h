#ifndef IA_H
#define IA_H

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

class Ia : protected Player
{
	public :
		Ia();

		int Height_Column(int j);
		int Lower_Position();
		int Height_Visualisation(int j, Piece p);
		int Choose_Rotation();
		bool IA_method(SDL_Renderer* renderer);
		Piece VisualPiece();

		bool input(SDL_Renderer* renderer);

		void render(SDL_Renderer* renderer, int frameCount, int lastFrame);

		void play(SDL_Renderer* renderer, bool running, bool end_b,
			SDL_Texture* gameover, int frameCount, int timerFPS, int lastFrame,
			int fps, SDL_Window* window);

};

#endif
