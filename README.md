![Futaba coding Puyo Puyo](http://i.imgur.com/cr7S8tq.gif)


À faire :
- FUCKING BUGS:
	- Bug aléatoire lors de l'appel d'apply seq dans evaluate_control (Control.cpp) <-- incompréhensible :(
	- A la création du game, next_couple est toujours le même que current_couple

	
Fait :
- Gestion du couple de puyos
- Fonctions de déplacement et de rotation du couple
- Adaptation du début de control.cpp aux couples (cf. fichier groove)
- Début de l'adaptation de la vue du Tetris
- Constructeur de gemu
- Destruction des groupes de puyos
- Comptage des points (https://www.bayoen.fr/wiki/Tableau_des_dommages)
- Gestion de la fin de la partie
- Interactions avec la vue
- Interactions avec l'IA