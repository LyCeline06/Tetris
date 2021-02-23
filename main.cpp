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
SDL_Texture *img = NULL;

int frameCount, timerFPS, lastFrame, fps;



void input(Board *board, const Uint8* keys)
{
	//if (keys[SDL_SCANCODE_RETURN])
	//	std::cout<< "<RETURN> is pressed."<< std::endl;


	if (keys[SDL_SCANCODE_UP])
		board->update(UP,renderer);

	if (keys[SDL_SCANCODE_DOWN])
		board->update(DOWN,renderer);

	if (keys[SDL_SCANCODE_LEFT])
        board->update(LEFT,renderer);

	if (keys[SDL_SCANCODE_RIGHT] )
    	board->update(RIGHT,renderer);
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
	time_t timer;
	time(&timer);
	const Uint8* state = SDL_GetKeyboardState(NULL);

    while(running) {
		SDL_Event event;
		while (running && SDL_PollEvent(&event)) //avoir attennte non bloquante
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("mouse click %d\n", event.button.button);
				break;
			default: break;
			}
		}

		if (time(nullptr)-timer > 0.5)	//gravity of current piece
		{
			board->gravity_piece(renderer);
			time(&timer);
		}

        lastFrame=SDL_GetTicks();
        if(lastFrame-lastTime >= 50)	//min speed to move pieces
		{
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
			input(board, state);

        }
		render();						//display piece and board
		board->draw_board(renderer);
		board->getcurPiece().draw_piece(renderer);
		SDL_RenderPresent(renderer);
	}

	//end game
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}
