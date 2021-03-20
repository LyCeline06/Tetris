#include "../include/Game.h"

#define BACKGROUND "utils/tetris.jpg"
#define MUSIC "utils/acapella.wav"
#define FONT "utils/police_style.ttf"
#define GAMEOVER "utils/gameover.bmp"
#define WIN "utils/win.jpg"


//************* AUDIO RELATED **************************************

Uint8 *audio_pos;  // global pointer to the audio buffer to be played
Uint32 audio_len;  // remaining length of the sample we have to play

// for playsong
void audio_cb(void *userdata, Uint8 *stream, int len) {
	len = ((unsigned int)len > audio_len ? audio_len : len);
	SDL_memcpy(stream, audio_pos, len);
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);

	audio_pos += len;
	audio_len -= len;

	(void)(userdata);
}
// for game(0)
void Game::entrymusic() {
	SDL_CloseAudio();

	if (SDL_LoadWAV(s.name, &s.wav_spec, &s.wav_buffer, &s.wav_length) ==
		NULL) {
		return;
	}

	// set the callback function
	s.wav_spec.callback = audio_cb;
	s.wav_spec.userdata = NULL;
	// set our global static variables
	s.audio_pos = s.wav_buffer;	 // copy sound buffer
	s.audio_len = s.wav_length;	 // copy file length

	// audio device
	if (SDL_OpenAudio(&s.wav_spec, NULL) < 0) {
		cout << "Couldn't open audio: \n" << SDL_GetError() << endl;
		return;
	}

	audio_pos = s.audio_pos;
	audio_len = s.audio_len;

	SDL_PauseAudio(0);
}

//************* CONSTRUCTOR/DESTRUCTOR ****************************

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << "Failed at SDL_Init()" << endl;

	window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, WIDTH_W * tile_size,
							  HEIGHT * tile_size,
							  SDL_WINDOW_RESIZABLE);

	if (!window) cout << "Could not create window" << SDL_GetError() << endl;

	renderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
		cout << "Could not create renderer \n" << SDL_GetError() << endl;



	SDL_GetRendererOutputSize(renderer, &width, &height);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);

	if (TTF_Init() < 0) cout << "Failed at TTF_Init" << endl;
	font = TTF_OpenFont(FONT, 100);	 // this opens a font style and sets a size
	if (!font) cout << "Failed at TTF_OpenFont" << TTF_GetError() << endl;

	// entry sound
	s.name = MUSIC;
	entrymusic();

	// background image
	surface = IMG_Load(BACKGROUND);
	if (!surface) cout << "Could not load image \n" << SDL_GetError() << endl;

	background = SDL_CreateTextureFromSurface(renderer, surface);
	if (!surface)
		cout << "Could not load image on background \n"
			 << SDL_GetError() << endl;

	// game-over
	image = SDL_LoadBMP(GAMEOVER);
	if (image == NULL)
		cout << "Could not load image for game-over \n"
			 << SDL_GetError() << endl;

	gameover = SDL_CreateTextureFromSurface(renderer, image);

		// background image
	image_win = IMG_Load(WIN);
	if (!surface) cout << "Could not load image \n" << SDL_GetError() << endl;

	win = SDL_CreateTextureFromSurface(renderer, image_win);

}

Game::~Game() {
	SDL_CloseAudio();
	if (s.wav_buffer != nullptr) SDL_FreeWAV(s.wav_buffer);
	SDL_FreeSurface(surface);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(gameover);
	SDL_DestroyTexture(background);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

//*****************************************************************
//*****************************************************************

void Game::menu() {
	bool start = false;
	while (!start && !end_b) {
		SDL_Event event;
		while (!start && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					end_b = true;
					break;
				// key pressed
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						// touche clavier
						case SDLK_RETURN:
							start = true;
							break;

						case SDLK_ESCAPE:
							end_b = true;
							break;
						case SDLK_1:
							start = true;
							gamemode = MODE_SOLO;
							break;
						case SDLK_2:
							start = true;
							gamemode = MODE_IA;
							break;
						default:
							break;
					}
					break;

				default:
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background, NULL, NULL);

		// TEXT
		SDL_Color White = {255, 255, 255, 255};
		SDL_Rect Message_rect;
		int w, h;
		SDL_GetWindowSize(window, &w, &h);

		// TETRIS
		surface = TTF_RenderText_Solid(font, "TETRIS", White);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		Message_rect.w = 500;
		Message_rect.h = 150;
		Message_rect.x = (w - Message_rect.w) * 0.5;
		Message_rect.y = (h - Message_rect.h) * 0.2;
		SDL_RenderCopy(renderer, texture, NULL, &Message_rect);

		// PRESS
		surface = TTF_RenderText_Solid(font, "PRESS 1 TO PLAY SOLO", White);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		Message_rect.w = 500;
		Message_rect.h = 75;
		Message_rect.x = (w - Message_rect.w) * 0.5;
		Message_rect.y = (h - Message_rect.h) * 0.5;
		if (fmod(SDL_GetTicks(), 500) > 50) {
			SDL_RenderCopy(renderer, texture, NULL, &Message_rect);
		}
		surface = TTF_RenderText_Solid(font, "PRESS 2 TO PLAY VS AI", White);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		Message_rect.w = 500;
		Message_rect.h = 75;
		Message_rect.x = (w - Message_rect.w) * 0.5;
		Message_rect.y = (h - Message_rect.h) * 0.7;
		if (fmod(SDL_GetTicks(), 300) > 50) {
			SDL_RenderCopy(renderer, texture, NULL, &Message_rect);
		}

		// CREATORS
		surface = TTF_RenderText_Solid(font, "BY CELINE & YASSINE", White);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		Message_rect.w = 250;
		Message_rect.h = 25;
		Message_rect.x = (w - Message_rect.w) * 0.5;
		Message_rect.y = (h - Message_rect.h) * 0.9;
		SDL_RenderCopy(renderer, texture, NULL, &Message_rect);
		SDL_RenderPresent(renderer);

		// AUDIO
		if (audio_len == 0) {
			audio_pos = s.audio_pos;
			audio_len = s.audio_len;
		}

		SDL_Delay(DELAY);
	}
};





void Game::start_solo()
{
	human.play(renderer, &running, end_b, gameover, frameCount,
		timerFPS, lastFrame, fps, window);
}

void Game::start_IA_solo()
{
	machine.play(renderer, &running, end_b, gameover, win, frameCount,
		timerFPS, lastFrame, fps, window, human);


}


void Game::start() {
	srand(time(NULL));

	if (gamemode == MODE_SOLO) start_solo();

	if (gamemode == MODE_IA) start_IA_solo();

	return;
};
