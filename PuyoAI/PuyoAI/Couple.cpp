#include "Couple.h"
#include "Shape.h"

// Chaque couple est initialisé avec deux puyos aléatoires, verticalement, dans la colonne 2
Couple::Couple() {
	puyos[0] = (Puyo)(rand() % 4);
	puyos[1] = (Puyo)(rand() % 4);
	orientation = DOWN;
	x_pos = 2;
	y_pos = 0;
	fallen = false;
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
	y_pos++;
}

// Bouge le couple vers la droite
void Couple::move_right() {
	x_pos++;
}

// Descend le couple d'une case
void Couple::move_left() {
	x_pos--;
}


// Rend les puyos
Puyo* Couple::get_puyos() {
	return puyos;
}

// Rend la valeur de la case (x, y) du tableau de forme du couple
int Couple::get_shape_value(int x, int y) {
	return SHAPES[orientation][x][y];
}

// Retourne la valeur de fallen
bool Couple::is_fallen() {
	return fallen;
}

// Met fallen a vrai
void Couple::fall() {
	fallen = true;
}