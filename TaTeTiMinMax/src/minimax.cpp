#include <stdio.h>

#include "../include/minimax.h"
#include "../include/tablero.h"

int min(int n1, int n2) {
	if (n1 < n2) return n1;
	else return n2;
}

int max(int n1, int n2) {
	if (n1 > n2) return n1;
	else return n2;
}

int scorer(Tablero t) {
	if (diagonal(O, t) || fila(0, O, t) || fila(1, O, t) || fila(2, O, t) ||
		columna(0, O, t) || columna(1, O, t)  || columna(2, O, t) ) return 1;
	else if (diagonal(X, t) || fila(0, X, t) || fila(1, X, t) || fila(2, X, t) ||
		columna(0, X, t) || columna(1, X, t)  || columna(2, X, t) ) return -1;
	else return 0;
}

int minimax(Tablero t, bool isMaximizing, int &cont) {
	int sc = scorer(t);
	if (t.res == 0 || sc != 0) {
	//	printf("%i\n",sc);
	//	showTablero(t);
		return sc;
	}
	int score, bestScore;
	if (isMaximizing) {
		bestScore = -10;
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				if (t.tab[i][j] == V ) {
					t.tab[i][j] = O;
					t.res --;
					cont ++;
					score = minimax(t, false, cont);
					t.tab[i][j] = V;
					t.res ++;
					bestScore = max(score, bestScore);
				}
		return bestScore;
		
	} else {
		bestScore = 10;
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				if (t.tab[i][j] == V ) {
					t.tab[i][j] = X;
					t.res --;
					cont ++;
					score = minimax(t, true, cont);
					t.tab[i][j] = V;
					t.res ++;
					bestScore = min(score, bestScore);
				}
		return bestScore;
	}
}

void juegoP(Tablero &t, bool &s) {
	if (s == true) {
		printf("juega la maquina\n");
		int contador = 0;
		int fil, col, score;
		int bestScore = -10;
		bool empate = true;
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				if (t.tab[i][j] == V ) {
					t.tab[i][j] = O;
					t.res --;
					score = minimax(t, false, contador);
					empate = empate && (score == 0); 
					t.tab[i][j] = V;
					t.res ++;
					if (score > bestScore) {
						bestScore = score;
						fil = i;
						col = j;
					}
				}
		t.tab[fil][col] = O; 
		t.res --;
		showTablero(t);
		printf("casos analizados %i\n", contador);
		if (bestScore == 1) printf("Ya perdiste capo \n");
		if (Decision(t, fil, col, O)) {
			printf("Perdiste !\n");
			s = false;
			return;
		}
		if (t.res == 1) {
			s = false;
			printf("Empate \n");
			return;
		}
		if (empate) {
			printf("es un empate asegurado\n");
			if (t.res == 1 )s = false;
			return;
		}

	}
}

