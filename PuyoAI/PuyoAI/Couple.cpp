#include "Couple.h"

// Chaque couple est initialisé avec deux puyos aléatoires, verticalement, dans la colonne 2
Couple::Couple() {
	puyos[0] = (Puyo)(rand() % 4);
	puyos[1] = (Puyo)(rand() % 4);
	orientation = DOWN;
	x_pos = 2;
	y_pos = 0;
}

// Attribue au couple l'orientation donnée en paramètre
void Couple::rotate_couple(int o) {
	orientation = o;
}

// Retourne l'orientation du couple
int Couple::get_orientation() {
	return orientation;
}

// Retourne la coordonnée x du couple
int Couple::get_xpos() {
	return x_pos;
}
// Retourne la coordonnée y du couple
int Couple::get_ypos() {
	return y_pos;
}

// Descend le couple d'une case
void Couple::move_down() {
	y_pos--;
}