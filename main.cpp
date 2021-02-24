#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Shape.h"
#include "Board.h"
#include "Piece.h"
#include "score.h"

bool running;
bool correct_line = false;
SDL_Renderer * renderer;
SDL_Window * window;

int frameCount, timerFPS, lastFrame, fps;
SDL_Surface * image = SDL_LoadBMP("gameover.bmp");

extern TTF_Font * font;


bool input(Board * board,const Uint8 * keys)
{
    //if (keys[SDL_SCANCODE_RETURN])
    //	std::cout<< "<RETURN> is pressed."<< std::endl;

    bool b = true;
    if (keys[SDL_SCANCODE_UP])
        b = board -> update(UP, renderer, &correct_line);

    if (keys[SDL_SCANCODE_DOWN])
        b = board -> update(DOWN, renderer, &correct_line);

    if (keys[SDL_SCANCODE_LEFT])
        b = board -> update(LEFT, renderer, &correct_line);

    if (keys[SDL_SCANCODE_RIGHT])
        b = board -> update(RIGHT, renderer, &correct_line);

    if (keys[SDL_SCANCODE_ESCAPE])
        running = false;
    else {
        b = board -> absorb();
    }
    return b;
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, (WIDTH)*tile_size, 0, (WIDTH)*tile_size,(HEIGHT+1)*tile_size);
    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / 60))
        SDL_Delay((1000 / 60) - timerFPS);

}

int main(int argc, char ** argv) {

    srand(time(NULL));
    bool b2 = true;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
    if (SDL_CreateWindowAndRenderer(WIDTH_W * tile_size, HEIGHT * tile_size, 0, & window, & renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;
    SDL_SetWindowTitle(window, "Tetris");
    init_score();

    Board * board = new Board();
    static int lastTime = 0;
    running = 1;
    time_t timer;
    time( & timer);
    const Uint8 * state = SDL_GetKeyboardState(NULL);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);

    while (running) {
        SDL_Event event;
        while (running && SDL_PollEvent( & event)) //avoir attennte non bloquante
        {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                printf("mouse click %d\n", event.button.button);
                break;
            default:
                break;
            }
        }

        if (time(nullptr) - timer > 0.5) //gravity of current piece
        {
            board -> gravity_piece(renderer, &correct_line);
            time( & timer);
        }

        lastFrame = SDL_GetTicks();
        if (lastFrame - lastTime >= 50) //min speed to move pieces
        {
            lastTime = lastFrame;
            fps = frameCount;
            frameCount = 0;
            b2 = input(board, state);

        }
        render();
        if (b2) {
            board -> draw_board(renderer);
            board -> getcurPiece().draw_piece(renderer);
            render_score();
            SDL_RenderPresent(renderer);

        } else {
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);

        }
    }

    //end game
    /* Deinit TTF. */
    SDL_DestroyTexture(texture1);
    SDL_DestroyTexture(texture2);
    TTF_Quit();

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
