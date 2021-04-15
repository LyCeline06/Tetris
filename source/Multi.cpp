#include "../include/Multi.h"

Multi::Multi() : Player() {}

int Multi::recv_msg(int sockfd) {
	int msg = 0;
	int n = read(sockfd, &msg, sizeof(int));

	if (n < 0 || n != sizeof(int))
		perror("ERROR reading int from server socket");

	// printf("[DEBUG] Received int: %d\n", msg);
	return msg;
}

bool Multi::input(SDL_Renderer *renderer, bool *running, int player,
				   Player humany) {
	bool b = true;
	int msg;

	msg = recv_msg(player);
	Board *board = humany.get_board();
	pair<int,int> correct_line = humany.get_correct_line();

	switch (msg) {
		case 1:
			board->update(UP, renderer, &correct_line);
			break;
		case 2:
			board->update(DOWN, renderer, &correct_line);
			break;
		case 3:
			board->update(LEFT, renderer, &correct_line);
			break;
		case 4:
			board->update(RIGHT, renderer, &correct_line);
			break;
		default:
			break;
	}

	if (msg == 5) {
		*running = false;
	} else
		b = board->absorb();
	// perror("Unknown message.");

	return b;
}
void Multi::render(SDL_Renderer *renderer, int frameCount, int lastFrame) {
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

// Returns fd of the listener socket
int Multi::setup_listener(int portno) {
	int sockfd;
	struct sockaddr_in serv_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) perror("ERROR opening listener socket.");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		perror("ERROR binding listener socket.");

	printf("[DEBUG] Listener set.\n");

	return sockfd;
}

void Multi::get_client(int lis_sockfd, int *cli_sockfd) {
	int player_count = 0;

	socklen_t clilen;
	// struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;

	int num_conn = 0;
	while (num_conn < 2) {
		listen(lis_sockfd, 253 - player_count);

		memset(&cli_addr, 0, sizeof(cli_addr));

		clilen = sizeof(cli_addr);

		cli_sockfd[num_conn] =
			accept(lis_sockfd, (struct sockaddr *)&cli_addr, &clilen);

		if (cli_sockfd[num_conn] < 0)
			perror("ERROR accepting a connection from a client.");

		write(cli_sockfd[num_conn], &num_conn, sizeof(int));

		player_count++;
		printf("Number of players is now %d.\n", player_count);

		num_conn++;
	}
}

void Multi::play(SDL_Renderer *renderer, bool running, bool end_b,
				 SDL_Texture *gameover, SDL_Texture *win, int frameCount,
				 int timerFPS, int lastFrame, int fps, SDL_Window *window,
				 Player1 humany) {
	SDL_SetWindowSize(window, WIDTH * 4 * tile_size, HEIGHT * tile_size);
	bool b2 = true;
	bool bai2 = true;
	static int lastTime = 0;
	running = 1;
	time_t timer;
	time(&timer);
	Score score((char*)"SCORE P1", 0, 40, renderer,0);
	Level level((char*)"LEVEL P1", 4*tile_size, 1, renderer,0);
	Lines lines((char*)"LINES P1", 8*tile_size, 1, renderer,0);


	Score score_p2((char*)"SCORE P2", 0, 40, renderer,1);
	Level level_p2((char*)"LEVEL P2",4*tile_size, 1, renderer,1);
	Lines lines_p2((char*)"LINES P2", 8*tile_size, 1, renderer,1);
	// Etats kyb
	// const Uint8 *state = SDL_GetKeyboardState(NULL);

	lis_sockfd = setup_listener(5555);
	cli_sockfd = (int *)malloc(2 * sizeof(int));
	memset(cli_sockfd, 0, 2 * sizeof(int));

	get_client(lis_sockfd, cli_sockfd);

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
			humany.board->gravity_piece(renderer, &humany.correct_line);
			time(&timer);
		}
		lastFrame = SDL_GetTicks();
		if (lastFrame - lastTime >= 70)	 // min speed to move pieces
		{
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;

			bai2 = input(renderer, &running, cli_sockfd[1], *this);
			b2 = input(renderer, &running, cli_sockfd[0], humany);
		}

		render(renderer, frameCount, lastFrame);  // display piece and board

		if (b2 && bai2) {
			render(renderer, frameCount, lastFrame);  // display piece and board
			// board -> draw_board(renderer, WIDTH*2*tile_size);
			humany.board->draw_board(renderer, 0);
			humany.board->getcurPiece().draw_piece(renderer);
			board->draw_board(renderer, WIDTH * 2 * tile_size);
			board->getcurPiece().draw_piece(renderer, WIDTH * 2);
            score.render_stat(&humany.correct_line);
			lines.render_stat(&humany.correct_line);
			level.render_stat(&humany.correct_line, &humany.speed, &humany.level_);
            score_p2.render_stat(&correct_line);
			lines_p2.render_stat(&correct_line);
			level_p2.render_stat(&correct_line, &speed, &level_);			
			SDL_RenderPresent(renderer);

		} else {
			SDL_Rect rec;
			if (!b2) {
				rec.w = WIDTH * tile_size;
				rec.h = HEIGHT * tile_size;
				rec.x = 0;
				rec.y = 0;
				SDL_RenderCopy(renderer, gameover, NULL, &rec);
				rec.w = WIDTH * tile_size;
				rec.h = HEIGHT * tile_size;
				rec.x = 2 * WIDTH * tile_size;
				rec.y = 0;
				SDL_RenderCopy(renderer, win, NULL, &rec);
			} else {
				rec.w = WIDTH * tile_size;
				rec.h = HEIGHT * tile_size;
				rec.x = 0;
				rec.y = 0;
				SDL_RenderCopy(renderer, win, NULL, &rec);
				rec.w = WIDTH * tile_size;
				rec.h = HEIGHT * tile_size;
				rec.x = 2 * WIDTH * tile_size;
				rec.y = 0;
				SDL_RenderCopy(renderer, gameover, NULL, &rec);
			}

            score.render_stat(&humany.correct_line);
			lines.render_stat(&humany.correct_line);
			level.render_stat(&humany.correct_line, &humany.speed, &humany.level_);
            score_p2.render_stat(&correct_line);
			lines_p2.render_stat(&correct_line);
			level_p2.render_stat(&correct_line, &speed, &level_);
			SDL_RenderPresent(renderer);
		}
	}

	free(cli_sockfd);
	close(lis_sockfd);
}
