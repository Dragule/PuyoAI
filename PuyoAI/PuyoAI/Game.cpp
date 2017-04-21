#include "Game.h"

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
void Game::drop_puyo(Puyo p, int x, int y) {
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