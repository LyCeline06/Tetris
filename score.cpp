#include "score.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Board.h"

extern SDL_Renderer* renderer;
extern int correct_line;


TTF_Font * font = NULL;
SDL_Rect rect1, rect2;
SDL_Texture * texture1, * texture2;
char msg1[6] = "SCORE";
char msg2[1000000] = "0";
int score = 0;
std::string font_path = "banksia.ttf";

void get_text_and_rect(SDL_Renderer * renderer, int x, int y, char * text,
TTF_Font * font, SDL_Texture ** texture, SDL_Rect * rect)
{
    int text_width;
    int text_height;
    SDL_Surface * surface;
    SDL_Color textColor = {
        255,
        255,
        255,
        0
    };

    surface = TTF_RenderText_Solid(font, text, textColor);
    * texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface -> w;
    text_height = surface -> h;
    SDL_FreeSurface(surface);
    rect -> x = x;
    rect -> y = y;
    rect -> w = text_width;
    rect -> h = text_height;
}

void init_score()
{

    /* Inint TTF. */
    TTF_Init();
    font = TTF_OpenFont(font_path.c_str(), 60);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text_and_rect(renderer, (WIDTH+4)*tile_size, 2*tile_size, msg1, font, & texture1, & rect1);
    get_text_and_rect(renderer, (WIDTH+4)*tile_size, 4 + rect1.y + rect1.h, msg2, font, & texture2, & rect2);

}

void render_score()
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    /* Use TTF textures. */
    SDL_RenderCopy(renderer, texture1, NULL, & rect1);
    SDL_RenderCopy(renderer, texture2, NULL, & rect2);

	if (correct_line)
	{
		printf("score\n" );
		score += 1000;
		sprintf(msg2, "%i", score);
		correct_line = false;
		get_text_and_rect(renderer, (WIDTH+4)*tile_size, 4 + rect1.y + rect1.h, msg2, font, & texture2, & rect2);
	}
}
