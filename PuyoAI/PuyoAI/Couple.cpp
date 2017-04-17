#include "Couple.h"

// Chaque couple est initialisé avec deux puyos aléatoires, verticalement, dans la colonne 2
Couple::Couple() {
	puyos[0] = (Puyo)(rand() % 4);
	puyos[1] = (Puyo)(rand() % 4);
	orientation = DOWN;
	x_pos = 2;
	y_pos = 0;
}

// Tourne puyos[0] autour de puyos[1]
void rotate_left() {
	
}

// Tourne puyos[1] autour de puyos[0]
void rotate_right() {

}

