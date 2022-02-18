#include <stdio.h>

#include "../include/funciones.h"

void showTablero(Tablero t) {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++)
			switch (t.tab[i][j]) {
				case X : printf(" X ");
					 break;
				case O : printf(" O ");
					 break;
				default : printf("   ");
			} 
		printf("\n");
	}
	printf("\n");
			
}

bool fila(int fil, terna J, Tablero t) {
	bool res = true;
	for (int j=0; j<3; j++)
		res = res && (t.tab[fil][j] == J);
	return res;
}
bool columna(int col, terna J, Tablero t) {
	bool res = true;
	for (int j=0; j<3; j++)
		res = res && (t.tab[j][col] == J);
	return res;
}
bool diagonal(terna J, Tablero t) {
	bool res = true;
	for (int i=0; i<3; i++)
		res = res && (t.tab[i][i] == J);
	if (res == true) return true;
	res = true;
	for (int i=0; i<3; i++)
		res = res && (t.tab[i][2-i] == J);
	return res;

}
bool Decision(Tablero t, int fil, int col, terna J) {
	bool f = fila(fil, J, t);
	if (f == true) return true;
	bool c = columna(col, J, t);
	if (c == true) return true;
	if ((fil == 1 && col == 1) || (fil == 2 && col == 0) || (fil == 0 && col == 2) || (fil == 0 && col == 0) || (fil == 2 && col == 2))
		return diagonal(J, t);
	return false;
}