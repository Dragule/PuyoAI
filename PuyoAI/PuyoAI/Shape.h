#pragma once

static const int NB_ROTATIONS = 4;
static const int SIZE = 3;

int SHAPES[NB_ROTATIONS][SIZE][SIZE] =
{
	{
		{ 0, 1, 0 },
		{ 0, 2, 0 },
		{ 0, 0, 0 },
	},

	{
		{ 0, 0, 0 },
		{ 0, 2, 0 },
		{ 0, 1, 0 },
	},

	{
		{ 0, 0, 0 },
		{ 1, 2, 0 },
		{ 0, 0, 0 },
	},

	{
		{ 0, 0, 0 },
		{ 0, 2, 1 },
		{ 0, 0, 0 },
	}
};