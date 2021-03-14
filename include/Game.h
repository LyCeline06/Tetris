#ifndef GAME_H
#define GAME_H

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
#include "Board_AI.h"
#include "Piece.h"
#include "Shape.h"
using namespace std;

#define DELAY 25

// Audio structure to play song
struct Sound {
	const char* name;
	Uint8* audio_pos;
	Uint32 audio_len;
	Uint32 wav_length;
	Uint8* wav_buffer = nullptr;
	SDL_AudioSpec wav_spec;
};

const vector<float> speed = {0.48, 0.43, 0.38, 0.33, 0.28, 0.18, 0.13, 0.08, 0.06};
enum {MODE_SOLO, MODE_IA};

class Game {
   public:
	/* @brief Game constructor
	creates window , sound and background */
	Game();
	/* @brief Game menu
	creates window , sound and background */
	void menu();
	/* @brief plays entry sound  */
	void entrymusic();
	/* @brief Game destructor */
	~Game();

	void start();
	void start_solo();
	void start_ia();
	void render();
	bool input(Board* board, const Uint8* keys);
	bool input_ai(Board_ai* board, const Uint8* keys);	
	void change_level();
   private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	TTF_Font* font;

	Board *board;
	Board_ai *board_ai;
	Sound s;
	int correct_line;
	int correct_line_ai;
	float gravity_speed;
	int level;
	bool changed_lev;

	SDL_Texture* background;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int width;
	int height;
	SDL_Texture* gameover;
	SDL_Surface *image;

	int frameCount, timerFPS, lastFrame, fps;
	bool running;
	bool end_b = false;
	int gamemode;

};

#endif
