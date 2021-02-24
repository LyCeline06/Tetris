#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <cmath>
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

extern TTF_Font * font;
extern SDL_Rect rect1, rect2;
extern SDL_Texture * texture1, * texture2;
extern char msg1[6];
extern char msg2[1000000];
extern int score;
extern std::string font_path;


void get_text_and_rect(SDL_Renderer * renderer, int x, int y, char * text,
TTF_Font * font, SDL_Texture ** texture, SDL_Rect * rect);

void init_score();

void render_score();


#endif
