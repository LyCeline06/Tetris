#ifndef MULTI_H
#define MULTI_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include <cmath>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

#include "Board.h"
#include "Piece.h"
#include "Player.h"
#include "Player1.h"
#include "Shape.h"
#include "Stat.h"

class Player1;

class Multi : protected Player {
   public:
	int lis_sockfd;
	int* cli_sockfd;

	Multi();

	bool input(SDL_Renderer* renderer, bool* running, int player,
				Player humany);

	void render(SDL_Renderer* renderer, int frameCount, int lastFrame);

	void play(SDL_Renderer* renderer, bool running, bool end_b,
			  SDL_Texture* gameover, SDL_Texture* win, int frameCount,
			  int timerFPS, int lastFrame, int fps, SDL_Window* window,
			  Player1 humany);

	// Returns fd of the listener socket
	int setup_listener(int portno);
	void get_client(int lis_sockfd, int* cli_sockfd);

	int recv_msg(int sockfd);

	friend class Player1;
};

#endif
