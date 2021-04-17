#include "../include/Client.h"

Client::Client() : Player() {}

void Client::error(const char *msg) {
	perror(msg);
	printf(
		"Player disconnected or server shutdown.\nGame "
		"over.\n");

	exit(0);
}

void Client::write_server_msg(int cli_sockfd, int msg) {
	int n = write(cli_sockfd, &msg, sizeof(int));
	if (n < 0) error("Writing msg to server socket failed\n");
}

int Client::connect_to_server(const char *hostname, int portno) {
	struct sockaddr_in serv_addr;
	struct hostent *server;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) error("Opening socket for server failed.");

	server = gethostbyname(hostname);

	if (server == NULL) {
		fprintf(stderr, "No host\n");
		exit(0);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	memmove(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("Connecting to server failed");

	printf("Connected to server.\n");
	return sockfd;
}

void Client::input(const Uint8 *keys, int sockfd) {
	if (keys[SDL_SCANCODE_UP]) write_server_msg(sockfd, 1);

	if (keys[SDL_SCANCODE_DOWN]) write_server_msg(sockfd, 2);

	if (keys[SDL_SCANCODE_LEFT]) write_server_msg(sockfd, 3);

	if (keys[SDL_SCANCODE_RIGHT]) write_server_msg(sockfd, 4);

	if (keys[SDL_SCANCODE_ESCAPE]) write_server_msg(sockfd, 5);

	if (!(keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_DOWN] ||
		  keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_RIGHT] ||
		  keys[SDL_SCANCODE_ESCAPE]))
		write_server_msg(sockfd, -1);
}

void Client::render(SDL_Renderer *renderer, int frameCount, int lastFrame) {
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

void Client::play(SDL_Renderer *renderer, bool running, bool end_b,
				  SDL_Texture *gameover, SDL_Texture *multi, int frameCount,
				  int timerFPS, int lastFrame, int fps, SDL_Window *window) {
	int sockfd;
	int first_time = 0;
	SDL_SetWindowSize(window, WIDTH * 2 * tile_size, HEIGHT * 1.5 * tile_size);
	SDL_Rect rec;
	rec.w = 2 * WIDTH * tile_size;
	rec.h = 1.5 * HEIGHT * tile_size;
	rec.x = 0;
	rec.y = 0;
	SDL_RenderCopy(renderer, multi, NULL, &rec);
	SDL_RenderPresent(renderer);

	// bool b2 = true;
	static int lastTime = 0;
	running = 1;
	time_t timer;
	time(&timer);

	// Etats kyb
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	SDL_Event event;

	while (!first_time) {
		SDL_WaitEvent(&event);

		switch (event.type) {
			case SDL_KEYDOWN:
				printf("The %s key was pressed!\n",
					   SDL_GetKeyName(event.key.keysym.sym));
				if (event.key.keysym.sym == SDLK_1) {
					sockfd = connect_to_server("10.10.10.10", 5555);
					first_time = 1;
					printf("ok");
				}
				if (event.key.keysym.sym == SDLK_2) {
					sockfd = connect_to_server("12.12.12.12", 5555);
					first_time = 1;
				}

				break;
			default:
				printf("Please press 1 or 2 !\n");
				break;
		}
	}

	while (running && !end_b) {
		SDL_Event event;

		while (running &&
			   SDL_PollEvent(&event))  // avoir attennte non bloquante
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
			input(state, sockfd);
		}

		render(renderer, frameCount, lastFrame);
	}
}
