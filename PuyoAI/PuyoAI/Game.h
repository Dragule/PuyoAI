#pragma once

using namespace std;

#include <cstdint>
#include <array>
#include <random>

#include "Couple.h"

static const int FREE = -1;
static const int BOARD_HEIGHT = 12;
static const int BOARD_WIDTH = 6;

/*
						TOP

				   0   1   2   3         BOARD_WIDTH - 1
				 +---+---+---+---+           +---+
			0	 |   |   |   |   |    ...    |   |
				 +---+---+---+---+           +---+
			1	 |   |   |   |   |    ...    |   |
				 +---+---+---+---+           +---+
			2	 |   |   |   |   |    ...    |   |
				 +---+---+---+---+           +---+
			.
			.
			.
				 +---+---+---+---+           +---+
BOARD_HEIGHT - 1 |   |   |   |   |    ...    |   |
				 +---+---+---+---+           +---+

					  BOTTOM
*/


class Game
{
	array<array<int8_t, BOARD_WIDTH>, BOARD_HEIGHT> board;
	Couple current_couple;
public :
	bool is_free(int x, int y);
	void rotate_left();
	void rotate_right();
	void drop_couple();
	void drop_puyo(Puyo p, int x, int y);
};