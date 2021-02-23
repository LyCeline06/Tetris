#include <SDL.h>
#include <iostream>
#include <cmath>


#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Shape.h"
#include "Board.h"
#include "Piece.h"
bool running;

SDL_Renderer* renderer;
SDL_Window* window;

int frameCount, timerFPS, lastFrame, fps;

Piece p;


void input(Board *board) {
    SDL_Event e;

    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT) running=false;
        switch( e.type ){
            case SDL_KEYUP: //DOWN
			printf("up\n");
                switch(e.key.keysym.sym) {
                    case SDLK_LEFT:
						printf("left\n");
                        board->update(LEFT,renderer);
                        break;
                    case SDLK_RIGHT:
                        board->update(RIGHT,renderer);
						printf("right\n");
                        break;
                    case SDLK_UP:
                        board->update(UP,renderer);
						printf("up\n");
                        break;
                    case SDLK_DOWN:
                        board->update(DOWN,renderer);
						printf("down\n");
                        break;
                    case SDLK_ESCAPE:
                        running=false;
                        break;
                }
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    frameCount++;
    int timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS<(1000/60))
        SDL_Delay((1000/60)-timerFPS);

}


int main(int argc, char **argv) {
    srand(time(NULL));
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
	if(SDL_CreateWindowAndRenderer(WIDTH*tile_size, HEIGHT*tile_size, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
	SDL_SetWindowTitle(window, "Tetris");

	Board *board = new Board();

    static int lastTime=0;
	running=1;
    while(running) {
        lastFrame=SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)) {
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
        }
		input(board);
		render();
		board->getcurPiece().draw_piece(renderer);
		SDL_RenderPresent(renderer);

	}


	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
