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
#include "tetris.hpp"
#include "view.hpp"
#include "control.hpp"
#include "cem.hpp"
#include <chrono>

using namespace std;
using namespace sf;

void play(const vector<double>& weights)
{
  mt19937 engine(chrono::system_clock::now().time_since_epoch().count());
  tetris game(engine);
  //ascii_view view;
  graphical_view view;
  heuristic_control control(weights);
  play_tetris(game, view, control, engine, 150u);
}

void learn()
{
  vector<double> weights; // TO DO: set the correct size
  cem cem(weights, 30, 50, 0.3, evaluate_control);
  cem.run();
}

int main(int argc, char *argv[])
{
  play({});
  return 0;
}
