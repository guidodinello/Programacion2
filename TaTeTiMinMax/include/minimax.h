#ifndef _Minmax_H
#define _Minmax_H

#include "tablero.h"
#include "funciones.h"

int min(int n1, int n2);
int max(int n1, int n2);
int scorer(Tablero t);
int minimax(Tablero t, bool isMaximizing, int &cont);
void juegoP(Tablero &t, bool &s);


#endif