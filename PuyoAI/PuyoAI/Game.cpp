#include "Game.h"

// Constructeur de game
Game::Game() { // A la création du game, le next_couple est toujours le même que le current_couple, sûrement à cause de l'imprécision du random, à corriger
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		for (int j = 0; j < BOARD_HEIGHT; ++j) {
			board[i][j] = FREE;
		}
	}
	hits = 0;
	score = 0;

	hits_max = 0;
	hit_start = 0;
	hits_total = 0;

	board[2][0] = current_couple.get_puyos()[0];
	board[2][1] = current_couple.get_puyos()[1];
}


// Vérifie si Justin Wong est présent dans la case board[x][y]
bool Game::is_free(int x, int y) {
	if (x >= 0 && x < BOARD_WIDTH && y >= 0 && y < BOARD_HEIGHT) return (board[x][y] == -1);
	return false;
}

// Tourne puyos[1] autour de puyos[0] dans le sens horaire
void Game::rotate_left() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (is_free(current_couple.get_xpos() + 1, current_couple.get_ypos())) {
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = FREE;
			current_couple.rotate_couple(RIGHT);
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case DOWN:
		if (is_free(current_couple.get_xpos() - 1, current_couple.get_ypos())) {
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = FREE;
			current_couple.rotate_couple(LEFT);
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case LEFT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() - 1)) {
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = FREE;
			current_couple.rotate_couple(UP);
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = current_couple.get_puyos()[1];
		}
		break;
	case RIGHT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) {
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = FREE;
			current_couple.rotate_couple(DOWN);
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = current_couple.get_puyos()[1];
		}
		break;
	}
}

// Tourne puyos[1] autour de puyos[0] dans le sens trigonométrique
void Game::rotate_right() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (is_free(current_couple.get_xpos() - 1, current_couple.get_ypos())) {
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = FREE;
			current_couple.rotate_couple(LEFT);
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case DOWN:
		if (is_free(current_couple.get_xpos() + 1, current_couple.get_ypos())) {
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = FREE;
			current_couple.rotate_couple(RIGHT);
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case LEFT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) {
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = FREE;
			current_couple.rotate_couple(DOWN);
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = current_couple.get_puyos()[1];
		}
		break;
	case RIGHT:
		if (is_free(current_couple.get_xpos(), current_couple.get_ypos() - 1)) {
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = FREE;
			current_couple.rotate_couple(UP);
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = current_couple.get_puyos()[1];
		}
		break;
	}
}

// Fait tomber le couple jusqu'à ce qu'un des deux puyos touche une colonne
void Game::drop_couple() {
	while (!current_couple.is_fallen()) move_down();
	destroy_all();
}

// Fait tomber un puyo donné jusqu'à ce qu'il touche
void Game::drop_puyo(int p, int x, int y) {
	int y2 = y;
	board[x][y2] = FREE;
	while (!current_couple.is_fallen()) {
		if (is_free(x, y2 + 1)) y2++;
		else { current_couple.fall(); }
	}
	board[x][y2] = p;
}

// Détruit tous les blocs de puyos
void Game::destroy_all() {
	vector<pair<int, int>> involved;
	int power_rangers[4] = { 0, 0, 0, 0 };
	bool b = false;
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		for (int j = 0; j < BOARD_HEIGHT; ++j) {
			pair<int,int> p = make_pair(i, j);
			if (!is_free(i, j) && !contains(involved, p)) {
				check(i, j, board[i][j]);
				if (destroy.size() > 3) {
					while(!destroy.empty()) {
						power_rangers[board[i][j]] += destroy.size();
						involved.push_back(destroy.back());
						destroy.pop_back();
						b = true;
					}
				}
				destroy.clear();
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
		int hits_value = min(hits, 18);
		score += ((power_rangers[0]+power_rangers[1]+power_rangers[2]+power_rangers[3])* 10)*(SCORE_HITPOWER[6] + SCORE_BONUS_COLORS[col_bon] + SCORE_BONUS_GROUPS[power_rangers[0]] + SCORE_BONUS_GROUPS[power_rangers[1]] + SCORE_BONUS_GROUPS[power_rangers[2]] + SCORE_BONUS_GROUPS[power_rangers[3]]);
		hits++;
		if (hits == 2) {
			hit_start++;
		}
		hits_total++;
		hits_max = max(hits_max, hits);
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
		if (y > 0) check(x, y - 1, p);
		// Down
		if (y < BOARD_HEIGHT - 1) check(x, y + 1, p);
		// Left
		if (x > 0) check(x - 1, y, p);
		// Right
		if (x < BOARD_WIDTH - 1) check(x + 1, y, p);
	}
}

// GAME OVER ?
bool Game::is_game_over() {
	if (board[2][0] != FREE) return true;
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

// Retourne le score actuel
int Game::get_score() const {
	return score;
}

// Retourne le nombre de shits actuel
int Game::get_hits() const {
	return hits;
}

// Retourne l'état du current couple
bool Game::is_current_couple_fallen() {
	return current_couple.is_fallen();
}

// Met le couple next_couple en current_couple et initialise un nouveau next_couple
void Game::next() {
	current_couple = next_couple;
	next_couple = Couple();

	board[2][0] = current_couple.get_puyos()[0];
	board[2][1] = current_couple.get_puyos()[1];
}

// Descend le couple d'un cran
void Game::move_down() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (!is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = FREE;
			current_couple.move_down();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = current_couple.get_puyos()[1];
		}
		break;
	case DOWN:
		if (!is_free(current_couple.get_xpos(), current_couple.get_ypos() + 2)) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			current_couple.move_down();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = current_couple.get_puyos()[1];
		}
		break;
		// Dans les cas left et right, quand un puyo touche, on laisse tomber l'autre séparément
	case LEFT:
		if (!is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) {
			drop_puyo(current_couple.get_puyos()[1], current_couple.get_xpos() - 1, current_couple.get_ypos());
			current_couple.fall();
		}
		else if (!is_free(current_couple.get_xpos() - 1, current_couple.get_ypos() + 1)) {
			drop_puyo(current_couple.get_puyos()[0], current_couple.get_xpos(), current_couple.get_ypos());
			current_couple.fall();
		}
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			board[current_couple.get_xpos() - 1 ][current_couple.get_ypos()] = FREE;
			current_couple.move_down();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case RIGHT:
		if (!is_free(current_couple.get_xpos(), current_couple.get_ypos() + 1)) {
			drop_puyo(current_couple.get_puyos()[1], current_couple.get_xpos() + 1, current_couple.get_ypos());
			current_couple.fall();
		}
		else if (!is_free(current_couple.get_xpos() + 1, current_couple.get_ypos() + 1)) {
			drop_puyo(current_couple.get_puyos()[0], current_couple.get_xpos(), current_couple.get_ypos());
			current_couple.fall();
		}
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = FREE;
			current_couple.move_down();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	}
}

void Game::move_left() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (!is_free(current_couple.get_xpos() - 1, current_couple.get_ypos())) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = FREE;
			current_couple.move_left();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = current_couple.get_puyos()[1];
		}
		break;
	case DOWN:
		if (!is_free(current_couple.get_xpos() - 1, current_couple.get_ypos() + 1)) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = FREE;
			current_couple.move_left();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = current_couple.get_puyos()[1];
		}
		break;
	case LEFT:
		if (!is_free(current_couple.get_xpos() - 2, current_couple.get_ypos())) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			current_couple.move_left();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case RIGHT:
		if (!is_free(current_couple.get_xpos() - 1, current_couple.get_ypos())) current_couple.fall();
		else {
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = FREE;
			current_couple.move_left();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	}
}

void Game::move_right() {
	switch (current_couple.get_orientation()) {
	case UP:
		if (!is_free(current_couple.get_xpos() + 1, current_couple.get_ypos())) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = FREE;
			current_couple.move_right();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos()][current_couple.get_ypos() - 1] = current_couple.get_puyos()[1];
		}
		break;
	case DOWN:
		if (!is_free(current_couple.get_xpos() + 1, current_couple.get_ypos() + 1)) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = FREE;
			current_couple.move_right();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos()][current_couple.get_ypos() + 1] = current_couple.get_puyos()[1];
		}
		break;
	case LEFT:
		if (!is_free(current_couple.get_xpos() + 1, current_couple.get_ypos())) current_couple.fall();
		else {
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = FREE;
			current_couple.move_right();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos() - 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	case RIGHT:
		if (!is_free(current_couple.get_xpos() + 2, current_couple.get_ypos())) current_couple.fall();
		else {
			board[current_couple.get_xpos()][current_couple.get_ypos()] = FREE;
			current_couple.move_right();
			board[current_couple.get_xpos()][current_couple.get_ypos()] = current_couple.get_puyos()[0];
			board[current_couple.get_xpos() + 1][current_couple.get_ypos()] = current_couple.get_puyos()[1];
		}
		break;
	}
}

// Retourne la taille du vecteur destroy
int Game::get_des_size() {
	return destroy.size();
}

// Retourne le hits_max
int Game::get_hits_max() {
	return hits_max;
}

// Calcule la moyenne de nombre de hits par chaines
int Game::get_hits_mean() {
	if (hit_start == 0) return 0;
	return (int) (hits_total / hit_start);
}