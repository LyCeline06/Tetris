#include "../include/IA.h"

Ia::Ia() : Player()
{}


int Ia::Height_Column(int j){
	for (int i=0;i<HEIGHT;i++)
		if (board->get_Board()[i][j].g!=0) return HEIGHT-i;
	return 0;
}

int Ia::Lower_Position(){
	int j=0;
	int res=HEIGHT;
	Piece curPiece = board->getcurPiece();
	int hei=curPiece.hei();
	int wid=curPiece.wid();
	if (wid<hei)
		{for (int k=0;k<=WIDTH-wid;k++){
			int h=Height_Column(k);
			for(int l=0;(l<wid);l++)
				if (Height_Column(k+l)>h)
					h=Height_Column(k+l);
			if (h<res){
				j=k;
				res=h;
			}
		}
		return j;}
	else
	{for (int k=0;k<=WIDTH-hei;k++){
		int h=Height_Column(k);
		for(int l=0;(l<hei);l++)
			if (Height_Column(k+l)>h)
				h=Height_Column(k+l);
		if (h<res){
			j=k;
			res=h;
		}
	}
	return j;}
}

int Ia::Height_Visualisation(int j, Piece p){
	int y=p.getY();
	int x2=p.Real_x();
	int x=p.getX();
	int hei=p.hei();
	p.setX(j+x2-x);
	while(board->fit(p)){
		y=p.getY();
		p.setY(y+1);
	}
	p.setY(y-1);
	return y+hei;

}

int Ia::Choose_Rotation(){
	Piece p= board->getcurPiece();
	int y=p.getY();
	Shape s = p.getShape();
	int j=Lower_Position();
	int val=Height_Visualisation(j,p);
	int l=0;
	for (int k=0;k<3;k++){
		Shape s2= rotate(s);
		s=s2;
		p.setShape(s2);
		p.setY(y);
		if (Height_Visualisation(j,p)>val){
			val=Height_Visualisation(j,p);
			l=k;
		}
	}
	return l;
}

bool Ia::IA_method(SDL_Renderer* renderer){
	int k=Choose_Rotation();
	int y=board->getcurPiece().getY();
	if (y==0){
		for (int l=0;l<k;l++)
			board->rotate2();
		}
	int j=Lower_Position();
	bool b;
	int x=board->getcurPiece().getX();
	if (x<j){
		b=board->update(RIGHT,renderer, &correct_line);
	}

	if (x>j){
		b=board->update(LEFT,renderer, &correct_line);
	}
	b=board->update(DOWN,renderer, &correct_line);
	return b;
}

Piece Ia::VisualPiece(){
	Piece p=board->getcurPiece();
	while (board->fit(p)){
		int y =p.getY();
		p.setY(y+1);
	}
	int y=p.getY();
	p.setY(y-1);
	Shape s=p.getShape();
	s.color={128,128,128,0};
	p.setShape(s);
	return p;

}


bool Ia::input(SDL_Renderer* renderer)
{
	bool b=true;
	b = IA_method(renderer);
	return b;
}

void Ia::render(SDL_Renderer* renderer, int frameCount, int lastFrame) {
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

void Ia::play(SDL_Renderer* renderer, bool running, bool end_b,
	SDL_Texture* gameover, SDL_Texture* win, int frameCount, int timerFPS, int lastFrame, int fps,
	SDL_Window* window, Player1 human) {

	srand(time(NULL));

	SDL_SetWindowSize(window, WIDTH*4*tile_size, HEIGHT*tile_size);

    bool b2 = true;
	bool bai2=true;
	static int lastTime = 0;
	running = 1;
	time_t timer;
	time(&timer);

	Score score((char*)"SCORE", 0, 40, renderer,0);
	Level level((char*)"LEVEL", 4*tile_size, 1, renderer,0);
	Lines lines((char*)"LINES", 8*tile_size, 1, renderer,0);


	Score score_AI((char*)"SCORE", 0, 40, renderer,1);
	Level level_AI((char*)"LEVEL", 4*tile_size, 1, renderer,1);
	Lines lines_AI((char*)"LINES", 8*tile_size, 1, renderer,1);

	// Etats kyb
	const Uint8 *state = SDL_GetKeyboardState(NULL);
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

		if (time(nullptr) - timer > speed)  // gravity of current piece
		{
			board->gravity_piece(renderer, &correct_line);
			human.board->gravity_piece(renderer, &human.correct_line);
			time(&timer);
		}
		lastFrame = SDL_GetTicks();
		if (lastFrame - lastTime >= 60)	 // min speed to move pieces
		{
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;
            b2 = human.input(state, renderer, &running);
		    bai2 = input(renderer);

		}

		render(renderer, frameCount, lastFrame);  // display piece and board

        if (b2 && bai2) {
			render(renderer, frameCount, lastFrame);  // display piece and board
            //board -> draw_board(renderer, WIDTH*2*tile_size);
			human.board -> draw_board(renderer, 0);
            human.board -> getcurPiece().draw_piece(renderer);
			board -> draw_board(renderer, WIDTH*2*tile_size);
            board -> getcurPiece().draw_piece(renderer, WIDTH*2);
            score.render_stat(&human.correct_line);
			lines.render_stat(&human.correct_line);
			level.render_stat(&human.correct_line, &human.speed, &human.level_);
            score_AI.render_stat(&correct_line);
			lines_AI.render_stat(&correct_line);
			level_AI.render_stat(&correct_line, &speed, &level_);
            SDL_RenderPresent(renderer);

        } else {
			SDL_Rect rec;
			if(!b2){
				rec.w=WIDTH*tile_size;
				rec.h=HEIGHT*tile_size;
				rec.x=0;
				rec.y=0;
	            SDL_RenderCopy(renderer, gameover, NULL, &rec);
				rec.w=WIDTH*tile_size;
				rec.h=HEIGHT*tile_size;
				rec.x=2*WIDTH*tile_size;
				rec.y=0;
	            SDL_RenderCopy(renderer, win, NULL, &rec);
			}
			else{
				rec.w=WIDTH*tile_size;
				rec.h=HEIGHT*tile_size;
				rec.x=0;
				rec.y=0;
	            SDL_RenderCopy(renderer, win, NULL, &rec);
				rec.w=WIDTH*tile_size;
				rec.h=HEIGHT*tile_size;
				rec.x=2*WIDTH*tile_size;
				rec.y=0;
	            SDL_RenderCopy(renderer, gameover, NULL, &rec);
			}

            score.render_stat(&human.correct_line);
			lines.render_stat(&human.correct_line);
			level.render_stat(&human.correct_line, &human.speed, &human.level_);
            score_AI.render_stat(&correct_line);
			lines_AI.render_stat(&correct_line);
			level_AI.render_stat(&correct_line, &speed, &level_);
            SDL_RenderPresent(renderer);

        }
			correct_line.second = 0;
			human.correct_line.second = 0;
	}
}
