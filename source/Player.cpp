#include "../include/Player.h"

Player::Player() : correct_line(0)
{
	board = new Board();
}

Board* Player::get_board()
{
	return board;
}

int Player::get_correct_line()
{
	return correct_line;
}
