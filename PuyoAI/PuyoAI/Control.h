#pragma once

#include "Game.h"
#include "View.h"
#include <chrono>
#include <functional>
#include <vector>
#include <algorithm>

template <typename View, typename Control>
void play_puyo(Game& g, View& view, Control& control, unsigned int milliseconds)
{
	using namespace std;
	auto wait = [&](unsigned int ms)
	{
		const chrono::system_clock::time_point start = chrono::system_clock::now();
		while (chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now() - start).count() < ms) view.draw(g);
	};
	view.draw(g);
	wait(milliseconds);
	while (true)
	{
		for (auto a : control(g))
		{
			switch (a) {
			case Game::ROTATE_LEFT:
				g.rotate_left();
				break;
			case Game::ROTATE_RIGHT:
				g.rotate_right();
				break;
			case Game::MOVE_DOWN:
				g.move_down();
				break;
			case Game::MOVE_LEFT:
				g.move_left();
				break;
			case Game::MOVE_RIGHT:
				g.move_right();
				break;
			case Game::DROP:
				g.drop_couple();
				break;
			}
			view.draw(g);
			wait(milliseconds);
		}
		if (g.is_current_couple_fallen())
		{
			if (g.is_game_over())
			{
				view.draw(g);
				break;
			}
			g.next();
		}
		view.draw(g);
		wait(milliseconds);
	}
}

struct heuristic_control
{
	const std::vector<double>& weights;
	heuristic_control(const std::vector<double>& weights);
	std::vector<Game::action> operator()(const Game& g);
	double evaluate_position(Game& g, int score_dif);
	static int apply_seq(Game& g, const std::vector<Game::action>& seq);
};

int evaluate_control(const std::vector<double>& weights);