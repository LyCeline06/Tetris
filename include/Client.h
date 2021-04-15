#ifndef Client_H
#define Client_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
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
#include "Shape.h"
#include "Stat.h"

class Client : protected Player {
   public:
	Client();

	void error(const char* msg);

	void write_server_msg(int cli_sockfd, int msg);

	int connect_to_server(const char* hostname, int portno);

	void render(SDL_Renderer* renderer, int frameCount, int lastFrame);

	void play(SDL_Renderer* renderer, bool running, bool end_b,
			  SDL_Texture* gameover, SDL_Texture* multi, int frameCount,
			  int timerFPS, int lastFrame, int fps, SDL_Window* window);

	void input(const Uint8* keys, int sockfd);
};

#endif
