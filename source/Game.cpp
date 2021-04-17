#include "../include/Game.h"


Uint8 *audio_position;  
Uint32 audio_length;  


void audio_cb(void *userdata, Uint8 *stream, int len) {
	len = ((unsigned int)len > audio_length ? audio_length : len);
	SDL_memcpy(stream, audio_position, len);
	SDL_MixAudio(stream, audio_position, len, SDL_MIX_MAXVOLUME);

	audio_position += len;
	audio_length -= len;

	(void)(userdata);
}

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

	audio_position = s.audio_pos;
	audio_length = s.audio_len;

	SDL_PauseAudio(0);
}


SDL_Texture* create_img(const char* file, SDL_Renderer* renderer){
	SDL_Surface* surface;
	SDL_Texture* background;
	surface = IMG_Load(file);
	if (!surface) cout << "Could not load image \n" << SDL_GetError() << endl;

	background = SDL_CreateTextureFromSurface(renderer, surface);
	if (!surface)
		cout << "Could not load image on background \n"
			 << SDL_GetError() << endl;
	return background;		 
}

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		cout << "Failed at SDL_Init()" << endl;

	window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED, WIDTH_W * tile_size,
							  HEIGHT * tile_size, SDL_WINDOW_RESIZABLE);

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

	background = create_img(BACKGROUND, renderer);
	gameover = create_img(GAMEOVER, renderer);
	win = create_img(WIN, renderer);
	client_img = create_img(CLIENT_IM, renderer);
}



Game::~Game() {
	SDL_CloseAudio();
	if (s.wav_buffer != nullptr) SDL_FreeWAV(s.wav_buffer);
	SDL_FreeSurface(surface);

	SDL_DestroyTexture(texture);
	SDL_DestroyTexture(gameover);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(win);
	SDL_DestroyTexture(client_img);
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



void Game::menu() {
	bool start = false;
	while (!start && !end_b) {
		SDL_Event event;
		while (!start && SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					end_b = true;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
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
						case SDLK_3:
							start = true;
							gamemode = MODE_MULTI;
							break;
						case SDLK_4:
							start = true;
							gamemode = MODE_CLIENT;
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

		// CREATORS 
		create_text("TETRIS", 500, 150, 0.5, 0.1, 607);
		create_text("PRESS 1 TO PLAY SOLO", 500, 55, 0.5, 0.4, 500);
		create_text( "PRESS 2 TO PLAY VS AI", 500, 55, 0.5, 0.55, 300);
		create_text("PRESS 3 FOR SERVER MODE", 550, 55, 0.5, 0.7, 350);
		create_text("PRESS 4 FOR CLIENT MODE", 550, 55, 0.5, 0.85, 400);
		create_text("BY CELINE & YASSINE", 250, 25, 0.5, 0.95, 310);
		
		SDL_RenderPresent(renderer);

		// AUDIO
		if (audio_length == 0) {
			audio_position = s.audio_pos;
			audio_length = s.audio_len;
		}

		SDL_Delay(DELAY);
	}
};

void Game::create_text(const char* text, float w_, float h_, float x_, float y_, int tick_){
		SDL_Color White = {255, 255, 255, 255};
		SDL_Rect Message_rect;
		int w, h;
		SDL_GetWindowSize(window, &w, &h);
		surface = TTF_RenderText_Solid(font, text, White);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		Message_rect.w = w_;
		Message_rect.h = h_;
		Message_rect.x = (w - Message_rect.w) * x_;
		Message_rect.y = (h - Message_rect.h) * y_;
		if (fmod(SDL_GetTicks(), tick_) > 50) {
			SDL_RenderCopy(renderer, texture, NULL, &Message_rect);
		}
		
}

void Game::start_solo() {
	human.play(renderer, &running, end_b, gameover, frameCount, timerFPS,
			   lastFrame, fps, window);
}

void Game::start_IA_solo() {
	machine.play(renderer, &running, end_b, gameover, win, frameCount, timerFPS,
				 lastFrame, fps, window, human);
}

void Game::start_multi() {
	multi.play(renderer, &running, end_b, gameover, win, frameCount, timerFPS,
			   lastFrame, fps, window, humany);
}

void Game::start_client() {
	client.play(renderer, &running, end_b, gameover, client_img, frameCount,
				timerFPS, lastFrame, fps, window);
}

void Game::start() {
	srand(time(NULL));

	if (gamemode == MODE_SOLO) start_solo();

	if (gamemode == MODE_IA) start_IA_solo();

	if (gamemode == MODE_MULTI) start_multi();

	if (gamemode == MODE_CLIENT) start_client();

	return;
};
