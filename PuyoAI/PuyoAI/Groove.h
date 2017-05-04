#pragma once
#include "Game.h"

static vector<vector<Game::action>> sequence =
{
	// Ne se d�place pas
	{ Game::DROP },

	// Se d�place sur la gauche sans rotation
	{ Game::MOVE_LEFT, Game::DROP },
	{ Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },

	// Se d�place sur la droite sans rotation
	{ Game::MOVE_RIGHT, Game::DROP },
	{ Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Tourne dans le sens trigonom�trique sans se d�placer
	{ Game::ROTATE_RIGHT, Game::DROP },
	// Tourne dans le sens trigonom�trique puis se d�place sur la gauche
	{ Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Tourne dans le sens trigonom�trique puis se d�place sur la droite
	{ Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Rotationne dans le sens horaire sans se d�placer
	{ Game::ROTATE_LEFT, Game::DROP },
	// Tourne dans le sens horaire puis se d�place sur la gauche
	{ Game::ROTATE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Tourne dans le sens horaire puis se d�place sur la droite
	{ Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Se retourne (deux rotations trigonom�triques) sans se d�placer
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::DROP },
	// Se retourne (deux rotations trigonom�triques) puis se d�place sur la gauche
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Se retourne (deux rotations trigonom�triques) puis se d�place sur la droite
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_RIGHT, Game::MOVE_DOWN, Game::ROTATE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },

	// Se retourne (deux rotations horaires) sans se d�placer
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::DROP },
	// Se retourne (deux rotations horaires) puis se d�place sur la gauche
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_LEFT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_LEFT, Game::MOVE_LEFT, Game::DROP },
	// Se retourne (deux rotations horaires) puis se d�place sur la droite
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
	{ Game::ROTATE_LEFT, Game::MOVE_DOWN, Game::ROTATE_LEFT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::MOVE_RIGHT, Game::DROP },
};