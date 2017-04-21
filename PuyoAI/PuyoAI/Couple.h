#pragma once

#include <time.h>
#include <random>

enum Puyo { BLUE = 0, GREEN, YELLOW, RED, OJAMA };
enum Orientation { UP = 0, DOWN, LEFT, RIGHT };

class Couple
{
	Puyo puyos[2];
	int orientation;
	int y_pos;
	int x_pos;
public:
	Couple();
	void rotate_couple(int o);

	Puyo* get_puyos();
	int get_orientation();
	int get_xpos();
	int get_ypos();

	void set_xpos();
	void set_ypos();
	void move_down();
};
