#include "../include/Player1.h"

Player1::Player1() : Player() {}

bool Player1::input(const Uint8* keys, SDL_Renderer* renderer, bool* running) {
	// if (keys[SDL_SCANCODE_RETURN])
	//	std::cout<< "<RETURN> is pressed."<< std::endl;
	bool b = true;

	if (keys[SDL_SCANCODE_UP]) {
		board->update(UP, renderer, &correct_line);
	}

	if (keys[SDL_SCANCODE_DOWN]) board->update(DOWN, renderer, &correct_line);

	if (keys[SDL_SCANCODE_LEFT]) board->update(LEFT, renderer, &correct_line);

	if (keys[SDL_SCANCODE_RIGHT]) board->update(RIGHT, renderer, &correct_line);

	if (keys[SDL_SCANCODE_ESCAPE])
		*running = false;
	else {
		b = board->absorb();
	}
	return b;
}

void Player1::render(SDL_Renderer* renderer, int frameCount, int lastFrame) {
	// set background color
	SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
	// apply
	SDL_RenderClear(renderer);

	frameCount++;
	int timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}
}
void Player1::play(SDL_Renderer* renderer, bool running, bool end_b,
				   SDL_Texture* gameover, int frameCount, int timerFPS,
				   int lastFrame, int fps, SDL_Window* window) {

		SDL_SetWindowSize(window, WIDTH * 2 * tile_size, HEIGHT * tile_size);


	bool b2 = true;
	static int lastTime = 0;
	running = 1;
	time_t timer;
	time(&timer);

	Stat score((char*)"SCORE", 0, 1000, 0, renderer);
	Stat level((char*)"LEVEL", 4 * tile_size, 1, 0, renderer);
	Stat lines((char*)"LINES", 8 * tile_size, 1, 1, renderer);


const Uint8 *state = SDL_GetKeyboardState(NULL);
while (running && !end_b) {
	SDL_Event event;
	while (running && SDL_PollEvent(&event))  // avoir attennte non bloquante
	{
		switch (event.type) {
			case SDL_QUIT:
				running = 0;
				printf("game quit\n");
				exit(1);
				break;
			case SDL_MOUSEBUTTONDOWN:
				printf("mouse click %d\n", event.button.button);
				break;
			default:
				// printf("non identified type of event\n");
				break;
		}
	}

	if (time(nullptr) - timer > 0.5)  // gravity of current piece
	{
		board->gravity_piece(renderer, &correct_line);
		time(&timer);
	}
	lastFrame = SDL_GetTicks();
	if (lastFrame - lastTime >= 70)	 // min speed to move pieces
	{
		lastTime = lastFrame;
		fps = frameCount;
		frameCount = 0;
		b2 = input(state, renderer, &running);
	}

	render(renderer, frameCount, lastFrame);  // display piece and board

	if (b2) {
		render(renderer, frameCount, lastFrame);  // display piece and board
		board->draw_board(renderer, 2);
		board->getcurPiece().draw_piece(renderer);
		score.render_stat(&correct_line);
		lines.render_stat(&correct_line);
		level.render_stat(&correct_line);
		SDL_RenderPresent(renderer);

	} else {
		SDL_Rect rec;
		rec.w = WIDTH * tile_size;
		rec.h = HEIGHT * tile_size;
			rec.x = 0;
		rec.y = 0;
		SDL_RenderCopy(renderer, gameover, NULL, &rec);
		score.render_stat(&correct_line);
		lines.render_stat(&correct_line);
		level.render_stat(&correct_line);
		SDL_RenderPresent(renderer);
	}
}
}
