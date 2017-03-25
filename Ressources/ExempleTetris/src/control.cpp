#include "control.hpp"

using namespace std;

heuristic_control::heuristic_control(const vector<double>& weights)
  : weights(weights)
{
}

static vector<vector<tetris::action>> sequence[NB_KINDS] =
  {
    { // O_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
    { // I_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP},

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
    { // S_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP},

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
    { // Z_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP},

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
    { // L_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
    { // J_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
    { // T_KIND
      { tetris::DROP },

      { tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN, tetris::ROTATE_RIGHT, tetris::MOVE_DOWN,tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_LEFT, tetris::DROP },

      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
      { tetris::MOVE_DOWN, tetris::ROTATE_LEFT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::MOVE_DOWN, tetris::MOVE_RIGHT, tetris::DROP },
    },
  };

bool heuristic_control::apply_seq(tetris& t, const vector<tetris::action>& seq, int& nb_lines)
{
  nb_lines = 0;
  for (uint8_t a : seq)
    {
      if (!t.do_action(tetris::action(a))) return false;
    }
  t.drop_current_piece();
  nb_lines = t.count_possible_lines();
  return true;
}

vector<tetris::action> heuristic_control::operator()(const tetris& t)
{
  vector<tetris::action> res = { tetris::DROP };
  double best_value = numeric_limits<double>::lowest();
  int current_piece_kind = t.get_current_piece().get_kind();
  int next_piece_kind = t.get_next_piece().get_kind();
  for (const auto& seq1 : sequence[current_piece_kind])
    {
      int nb_lines_seq1 = 0;
      tetris t1 = t;
      if (!apply_seq(t1, seq1, nb_lines_seq1)) continue;
      if (t1.is_game_over())
        {
          double v = evaluate_position(t1, nb_lines_seq1);
          if (v > best_value)
            {
              best_value = v;
              res = seq1;
            }
          continue;
        }
      t1.set_current_piece(t1.get_next_piece());
      for (const auto& seq2 : sequence[next_piece_kind])
        {
          tetris t2 = t1;
          int nb_lines_seq2;
          if (apply_seq(t2, seq2, nb_lines_seq2))
            {
              double v = evaluate_position(t2, nb_lines_seq1 + nb_lines_seq2);
              if (v > best_value)
                {
                  best_value = v;
                  res = seq1;
                }
            }
        }
    }
  return res;
}

double heuristic_control::evaluate_position(tetris& t, int nb_lines)
{
  /* TO DO */
  return 0;
}


int evaluate_control(const vector<double>& weights)
{
  const int NB_GAMES = 2;
  const int MAX_NB_ITERATIONS = 500;
  const int SEED = 27;
  using namespace std;
  mt19937 engine(SEED);
  heuristic_control control(weights);
  int res = 0;
  for (int i = 0; i < NB_GAMES; ++i)
    {
      tetris t(engine);
      int nb_iterations = 0;
      while (nb_iterations < MAX_NB_ITERATIONS)
        {
          ++nb_iterations;
          for (auto a : control(t))
            {
              t.do_action(a);
            }
          if (t.is_current_piece_fallen())
            {
              int nb_lines = t.delete_possible_lines();
              t.add_to_lines(nb_lines);
              t.add_to_score(nb_lines * nb_lines);
              if (t.is_game_over()) break;
              t.set_current_piece(t.get_next_piece());
              t.set_next_piece_at_random(engine);
            }
        }
      res += /* TO DO */0;
    }
  return res;
}
