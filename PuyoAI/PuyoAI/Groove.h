#pragma once
#include "Game.h"

static vector<vector<Game::action>> sequence =
{
	// Ne se déplace pas
	{ Game::DROP },

	// Se déplace sur la gauche sans rotation
	{ Game::MOVE_LEFT, Game::DROP },
	{ Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },

	// Se déplace sur la droite sans rotation
	{ Game::MOVE_RIGHT, Game::DROP },
	{ Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Tourne dans le sens trigonométrique sans se déplacer
	{ Game::ROTATE_RIGHT, Game::DROP },
	// Tourne dans le sens trigonométrique puis se déplace sur la gauche
	{ Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Tourne dans le sens trigonométrique puis se déplace sur la droite
	{ Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Rotationne dans le sens horaire sans se déplacer
	{ Game::ROTATE_LEFT, Game::DROP },
	// Tourne dans le sens horaire puis se déplace sur la gauche
	{ Game::ROTATE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Tourne dans le sens horaire puis se déplace sur la droite
	{ Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Se retourne (deux rotations trigonométriques) sans se déplacer
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::DROP },
	// Se retourne (deux rotations trigonométriques) puis se déplace sur la gauche
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Se retourne (deux rotations trigonométriques) puis se déplace sur la droite
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Se retourne (deux rotations horaires) sans se déplacer
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::DROP },
	// Se retourne (deux rotations horaires) puis se déplace sur la gauche
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_LEFT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Se retourne (deux rotations horaires) puis se déplace sur la droite
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
};