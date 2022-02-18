#ifndef _Func_H
#define _Func_H

#include "tablero.h"

void showTablero(Tablero t);
bool fila(int fil, terna J, Tablero t);
bool columna(int col, terna J, Tablero t);
bool diagonal(terna J, Tablero t);
bool Decision(Tablero t, int fil, int col, terna J);

#endif