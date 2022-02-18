#ifndef _Tablero_H
#define _Tablero_H

enum terna { O, X, V };

struct Tablero {
	terna tab[3][3];
	int res;
//true:cruz - false:circulo - null:vacio
};

Tablero copia(Tablero t);

#endif