#include "../include/Player.h"

Player::Player() : correct_line(make_pair(0, 0)), level_(0), speed(0.48) {
	board = new Board();
}

Board* Player::get_board() { return board; }

pair<int, int> Player::get_correct_line() { return correct_line; }

void Player::create_finalimage(int player, SDL_Texture* img,
							   SDL_Renderer* renderer) {
	SDL_Rect rec;
	rec.w = WIDTH * tile_size;
	rec.h = HEIGHT * tile_size;
	rec.x = player * WIDTH * tile_size;
	rec.y = 0;
	SDL_RenderCopy(renderer, img, NULL, &rec);
}
