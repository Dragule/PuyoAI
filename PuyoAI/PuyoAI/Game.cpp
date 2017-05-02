#include "Game.h"

// Constructeur de game
Game::Game() : current_couple(), next_couple() {
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		for (int j = 0; j < BOARD_HEIGHT; ++j) {
			board[i][j] = FREE;
		}
	}
	hits = 0;
	score = 0;
}


// Vérifie si Justin Wong est présent dans la case board[x][y]
bool Game::is_free(int x, int y) {
	if (x > 0 && x < BOARD_WIDTH && y > 0 && y < BOARD_HEIGHT) return (board[x][y] == -1);
	return false;
}

// Tourne puyos[1] autour de puyos[0] dans le sens horaire
void Game::rotate_left() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (is_free(current_couple.get_xpos() + 1, current_couple.get_ypos())) {
			current_couple.rotate_couple(RIGHT);
		}
	case DOWN:
		if (is_free(current_couple.get_xpos() - 1, current_couple.get_ypos())) {
			current_couple.rotate_couple(LEFT);
		}
	case LEFT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) {
			current_couple.rotate_couple(UP);
		}
	case RIGHT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() - 1)) {
			current_couple.rotate_couple(DOWN);
		}
	}
}

// Tourne puyos[1] autour de puyos[0] dans le sens trigonométrique
void Game::rotate_right() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (is_free(current_couple.get_xpos() - 1, current_couple.get_ypos())) current_couple.rotate_couple(LEFT);
	case DOWN:
		if (is_free(current_couple.get_xpos() + 1, current_couple.get_ypos())) current_couple.rotate_couple(RIGHT);
	case LEFT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() - 1)) current_couple.rotate_couple(DOWN);
	case RIGHT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) current_couple.rotate_couple(UP);
	}
}

// Fait tomber le couple jusqu'à ce qu'un des deux puyos touche une colonne
void Game::drop_couple() {
	bool fallen = false;
	switch (current_couple.get_orientation) {
	// Dans les cas up et down, les deux puyos s'arrêtent au même moment
	case UP:
		while (!fallen) {
			if (board[current_couple.get_xpos][current_couple.get_ypos + 1] != FREE) {
				board[current_couple.get_xpos][current_couple.get_ypos] == current_couple.get_puyos()[0];
				board[current_couple.get_xpos][current_couple.get_ypos - 1] == current_couple.get_puyos()[1];
				fallen = true;
			}
			else current_couple.move_down();
		}
	case DOWN:
		while (!fallen) {
			if (board[current_couple.get_xpos][current_couple.get_ypos + 2] != FREE) {
				board[current_couple.get_xpos][current_couple.get_ypos] == current_couple.get_puyos()[0];
				board[current_couple.get_xpos][current_couple.get_ypos + 1] == current_couple.get_puyos()[1];
				fallen = true;
			}
			else current_couple.move_down();
		}
	// Dans les cas left et right, quand un puyo touche, on laisse tomber l'autre séparément
	case LEFT:
		while (!fallen) {
			if (board[current_couple.get_xpos][current_couple.get_ypos + 1] != FREE) {
				board[current_couple.get_xpos][current_couple.get_ypos] == current_couple.get_puyos()[0];
				drop_puyo(current_couple.get_puyos()[1], current_couple.get_xpos - 1, current_couple.get_ypos);
				fallen = true;
			}
			else if (board[current_couple.get_xpos - 1][current_couple.get_ypos + 1] != FREE) {
				board[current_couple.get_xpos - 1][current_couple.get_ypos] == current_couple.get_puyos()[1];
				drop_puyo(current_couple.get_puyos()[0], current_couple.get_xpos, current_couple.get_ypos);
				fallen = true;
			}
			else current_couple.move_down();
		}
	case RIGHT:
		while (!fallen) {
			if (board[current_couple.get_xpos][current_couple.get_ypos + 1] != FREE) {
				board[current_couple.get_xpos][current_couple.get_ypos] == current_couple.get_puyos()[0];
				drop_puyo(current_couple.get_puyos()[1], current_couple.get_xpos + 1, current_couple.get_ypos);
				fallen = true;
			}
			else if (board[current_couple.get_xpos + 1][current_couple.get_ypos + 1] != FREE) {
				board[current_couple.get_xpos + 1][current_couple.get_ypos] == current_couple.get_puyos()[1];
				drop_puyo(current_couple.get_puyos()[0], current_couple.get_xpos, current_couple.get_ypos);
				fallen = true;
			}
			else current_couple.move_down();
		}
	}
}

// Fait tomber un puyo donné jusqu'à ce qu'il touche
void Game::drop_puyo(int p, int x, int y) {
	bool fallen;
	int y2 = y;
	while (!fallen) {
		if (board[x][y2 + 1] == FREE) y2++;
		else {
			board[x][y2] = p;
			fallen = true;
		}
	}
}

// Détruit tous les blocs de puyos
void Game::destroy_all() {
	vector<pair<int, int>> involved;
	int power_rangers[4] = { 0, 0, 0, 0 };
	bool b = false;
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		for (int j = 0; j < BOARD_HEIGHT; ++j) {
			pair<int,int> p = make_pair(i, j);
			if (board[i][j] != FREE && !contains(involved, p)) {
				check(i, j, board[i][j]);
				if (destroy.size > 3) {
					while(!destroy.empty) {
						power_rangers[board[i][j]] += destroy.size;
						involved.push_back(destroy.back);
						destroy.pop_back;
						b = true;
					}
				}
				destroy.clear;
			}
		}
	}
	for (int i = BOARD_WIDTH - 1; i >= 0; i--) {
		for (int j = BOARD_HEIGHT - 1; i >= 0; i--) {
			drop_puyo(board[i][j], i, j);
		}
	}
	if (b) {
		int col_bon = 0;
		for (int i = 0; i < 4; i++) {
			if (power_rangers[i] > 0) col_bon++;
		}
		// Formule de la puissance : https://www.bayoen.fr/wiki/Tableau_des_dommages
		score += ((power_rangers[0]+power_rangers[1]+power_rangers[2]+power_rangers[3])* 10)*(SCORE_HITPOWER[hits] + SCORE_BONUS_COLORS[col_bon] + SCORE_BONUS_GROUPS[power_rangers[0]] + SCORE_BONUS_GROUPS[power_rangers[1]] + SCORE_BONUS_GROUPS[power_rangers[2]] + SCORE_BONUS_GROUPS[power_rangers[3]]);
		hits++;
		destroy_all();
	}
	else {
		hits = 0;
	}
}

// Vérifie si un élément appartient à un vector<int> donné en paramètre
bool Game::contains(vector<pair<int, int>> v, pair<int, int> e) {
	if (std::find(v.begin(), v.end(), e) != v.end()) {
		return true;
	}
	else {
		return false;
	}
}

// Regarde si les puyos autour de la case donnée en paramètre sont de la même couleur que celui cette case et recommence si oui
void Game::check(int x, int y, int p) {
	if (!contains(destroy, make_pair(x, y)) && board[x][y] == p) {
		destroy.push_back(make_pair(x, y));
		// Up
		if (y > 1) check(x, y - 1, p);
		// Down
		if (y < BOARD_HEIGHT - 1) check(x, y + 1, p);
		// Left
		if (x > 1) check(x - 1, y, p);
		// Right
		if (x < BOARD_WIDTH - 1) check(x + 1, y, p);
	}
}

// GAME OVER ?
bool Game::is_game_over() {
	if (board[0][2] != FREE) return true;
	return false;
}

// Retourne la valeur de la case (x;y) du board
int Game::get(int x, int y) const {
	return board[x][y];
}

// Retourne le next_couple
Couple Game::get_next_couple() const {
	return next_couple;
}