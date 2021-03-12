#include "../include/Stat.h"


Stat::Stat(char *msg1, int nb, int score_base, int priority, SDL_Renderer *renderer) : font(nullptr), msg("0"), stat(0), nb(nb),
	score_base(score_base), priority(priority), renderer(renderer)
{

    /* Inint TTF. */
    TTF_Init();
    font = TTF_OpenFont("utils/Retro.ttf", 30);
    if (font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    get_text_and_rect(renderer, (WIDTH+2)*tile_size, (2*tile_size)+nb, msg1, font, & texture1, & rect1);
    get_text_and_rect(renderer, (WIDTH+2)*tile_size, 4 + rect1.y + rect1.h, msg, font, & texture2, & rect2);
	//width of text : 9 tile_size

}


void Stat::get_text_and_rect(SDL_Renderer * renderer, int x, int y, char * text,
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


void Stat::render_stat(int *correct)
{

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    /* Use TTF textures. */
    SDL_RenderCopy(renderer, texture1, NULL, & rect1);
    SDL_RenderCopy(renderer, texture2, NULL, & rect2);

	if (*correct)
	{
		printf("%i\n", *correct);
		stat += (*correct)*score_base;
		sprintf(msg, "%i", stat);
		if (priority)
			*correct = 0;
		printf("msg %s\n", msg);
		get_text_and_rect(renderer, (WIDTH+2)*tile_size, 4 + rect1.y + rect1.h, msg, font, & texture2, & rect2);
	}
}

Stat::~Stat()
{
	    SDL_DestroyTexture(texture1);
	    SDL_DestroyTexture(texture2);
	    TTF_Quit();
}
