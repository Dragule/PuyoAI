#pragma once

using namespace std;

#include <cstdint>
#include <array>
#include <random>
#include <algorithm>
#include <iostream>

#include "Couple.h"

static const int FREE = -1;
static const int BOARD_HEIGHT = 12;
static const int BOARD_WIDTH = 6;
static const int SCORE_HITPOWER[19] = { 0, 8, 16, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512 };
static const int SCORE_BONUS_COLORS[4] = { 0, 3, 6, 12 };
static const int SCORE_BONUS_GROUPS[11] = { 0, 0, 0, 0, 2, 3, 4, 5, 6, 7, 10 };

/*
x is WIDTH
y is HEIGHT

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
	std::array<std::array<int8_t, BOARD_HEIGHT>, BOARD_WIDTH> board;
	Couple current_couple;
	Couple next_couple;
	vector<pair<int, int>> destroy;
	int hits;
	int score;
	int hits_max;
	int hit_start;
	int hits_total;
public :
	enum action { ROTATE_LEFT, ROTATE_RIGHT, MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN, DROP };
	Game();
	bool is_free(int x, int y);
	void rotate_left();
	void rotate_right();
	void drop_couple();
	void drop_puyo(int p, int x, int y);
	void destroy_all();
	bool contains(vector<pair<int, int>> v, pair<int, int> e);
	void check(int x, int y, int p);
	bool is_game_over();
	int get(int x, int y) const;
	Couple get_next_couple() const;
	int get_score() const;
	int get_hits() const;
	bool is_current_couple_fallen();
	void next();
	void move_down();
	void move_left();
	void move_right();
	int get_des_size();
	int get_hits_max();
	int get_hits_mean();
};