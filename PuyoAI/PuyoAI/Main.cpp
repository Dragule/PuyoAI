#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <bitset>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <climits>
#include <cmath>
#include <stack>
#include <queue>
#include <cfloat>
#include <initializer_list>
#include <iomanip>
#include <functional>
#include <unordered_map>
#include <regex>
#include "Game.h"
#include "View.h"
#include "Control.h"
#include "cem.h"
#include <chrono>

using namespace std;
using namespace sf;

void play(const vector<double>& weights)
{
	Game game;
	//ASCII_View view;
	Graphical_View view;
	heuristic_control control(weights);
	play_puyo(game, view, control, 150u);
}

void learn()
{
	vector<double> weights(10);
	cem cem(weights, 30, 50, 0.3, evaluate_control);
	cem.run();
}

int main(int argc, char *argv[])
{

	learn();
	//play({ ... });
	return 0;
	
}
