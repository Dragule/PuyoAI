#include "Control.h"
#include "Groove.h"

heuristic_control::heuristic_control(const vector<double>& weights)
	: weights(weights) 
{
}

int heuristic_control::apply_seq(Game& g, const vector<Game::action>& seq)
{
	Game g1 = g;
	for (uint8_t a : seq) {
		if (g.is_current_couple_fallen()) break;

		switch (a) {
		case Game::ROTATE_LEFT :
			g.rotate_left();
			break;
		case Game::ROTATE_RIGHT :
			g.rotate_right();
			break;
		case Game::MOVE_DOWN :
			g.move_down();
			break;
		case Game::MOVE_LEFT :
			g.move_left();
			break;
		case Game::MOVE_RIGHT :
			g.move_right();
			break;
		case Game::DROP :
			g.drop_couple();
			break;
		}
	}
	g.drop_couple();
	return g.get_score() - g1.get_score();
}

vector<Game::action> heuristic_control::operator()(const Game& g)
{
	vector<Game::action> res = { Game::DROP };
	double best_value = numeric_limits<double>::lowest();
	for (const auto& seq1 : sequence) {
		int s1 = 0;
		Game g1 = g;
		s1 = apply_seq(g1, seq1);
		if (g1.is_game_over()) {
			double v = evaluate_position(g1, s1);
			if (v > best_value) {
				best_value = v;
				res = seq1;
			}
			continue;
		}
		g1.next();
		for (const auto& seq2 : sequence) {
			Game g2 = g1;
			int s2 = apply_seq(g2, seq2);
			double v = evaluate_position(g2, s1 + s2);
			if (v > best_value) {
				best_value = v;
				res = seq1;
			}
		}
	}
	return res;
}

double heuristic_control::evaluate_position(Game& g, int score_dif)
{
	int heights[6];
	int colors[4] = { 0, 0, 0, 0 };
	int max_h = 0;
	int min_h = 12;
	int nb_tri = 0;

	int res = 0.0;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (g.is_free(i, j)) {
				heights[i] = BOARD_HEIGHT - j;
				max_h = max(max_h, heights[i]);
				min_h = min(min_h, heights[i]);
			}
			else {
				colors[g.get(i, j)] = 1; 
				g.check(i, j, g.get(i, j));
				if (g.get_des_size() == 3) nb_tri++;
			}
		}
	}

	res += weights[0] * score_dif;
	res += weights[1] * heights[2];
	res += weights[2] * (heights[0] + heights[1] + heights[2] + heights[3] + heights[4] + heights[5]);
	res += weights[3] * (colors[0] + colors[1] + colors[2] + colors[3]);
	res += weights[4] * max_h;
	res += weights[5] * min_h;
	res += weights[6] * (max_h - min_h);
	res += weights[7] * nb_tri;
	res += weights[8] * g.get_hits_max();
	res += weights[9] * g.get_hits_mean();
	
	return res;
}

int evaluate_control(const vector<double>& weights)
{
	const int NB_GAMES = 2;
	const int MAX_NB_ITERATIONS = 500;
	using namespace std;
	heuristic_control control(weights);
	int res = 0;
	for (int i = 0; i < NB_GAMES; ++i) {
		Game g;
		int nb_iterations = 0;
		while (nb_iterations < MAX_NB_ITERATIONS) {
			++nb_iterations;
			heuristic_control::apply_seq(g, control(g));
			if (g.is_game_over()) break;
			g.next();
		}
		res += g.get_score() + g.get_hits();
	}
	return res;
}