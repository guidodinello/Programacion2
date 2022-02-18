#include "../include/tablero.h"

Tablero copia(Tablero t) {
	Tablero nuevo;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			nuevo.tab[i][j] = t.tab[i][j];
	nuevo.res = t.res;
	return nuevo;
}