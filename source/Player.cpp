#include "../include/Player.h"

Player::Player() : correct_line(make_pair(0,0)), level_(0), speed(0.48)
{
	board = new Board();
}

Board* Player::get_board()
{
	return board;
}

pair<int,int> Player::get_correct_line()
{
	return correct_line;
}
