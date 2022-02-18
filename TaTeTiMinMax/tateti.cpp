#include <stdio.h>
#include <stdlib.h> //rand()
#include <unistd.h> //getpid() 

#include "tablero.h"
#include "minimax.h"
#include "funciones.h"

void error() {	printf("jugada invalida, elija otra\n"); }

void InicioTablero(Tablero &t) {
	t.res = 9;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			t.tab[i][j] = V;
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++)
			printf("%i%i   ", i, j);
		printf("\n");
	}
}

void TurnoH(Tablero &t, bool &s) {
	printf("Es su turno \n");
	int mov,fil,col;
	do {
		scanf("%i", &mov);
		col = mov % 10;
		fil = (mov - col) / 10;
	} while (mov < 0 || fil >=3 || col >=3 || t.tab[fil][col] != V);
	t.tab[fil][col] = X;
	t.res --;
	showTablero(t);
	if (Decision(t, fil, col, X)) {
		printf("Ganaste !\n");
		s = false;
	}
}

void TurnoM(Tablero &t, bool &s) {
	if (s == true) {
		printf("juega la maquina\n");
		int fil,col;
		do {
			col = rand() % 3;
			fil = rand() % 3;
		} while (t.tab[fil][col] != V);
		t.tab[fil][col] = O;
		t.res --;
		showTablero(t);
		if (Decision(t, fil, col, O)) {printf("Perdiste !\n");}
	}
}

void insertar(Tablero &t, int fil, int col, terna J) {
	t.tab[fil][col] = J;
}

void hum(Tablero &t, bool &s) {
	if (s == true) {
		Tablero cop; 
		bool gana = false;
		bool nop = false;
		for (int i=0; i<3 && gana == false; i++)
			for (int j=0; j<3 && gana == false; j++) {
				cop = copia(t);
				if (cop.tab[i][j] == V) {
					insertar(cop, i, j, O);
					if (Decision(cop, i, j, O)) {//chequea si puede ganar en 1
						t.tab[i][j] = O;
						gana = true;
						printf(">>> puedo ganar <<<\n");
					}
				}
			}
		for (int i=0; i<3 && gana == false && nop == false; i++)
			for (int j=0; j<3 && gana == false && nop == false; j++) {
				cop = copia(t);
				if (cop.tab[i][j] == V) {
					insertar(cop, i, j, X);
					if (Decision(cop, i, j, X)) {//chequea no perder en 1
						t.tab[i][j] = O;
						nop = true;
						printf(">>> no me ganaras <<<\n");
					}
				}
			}
		if (gana == true) {
			s = false;
			t.res --;
			showTablero(t);
			printf("Perdiste !\n");
			return;
		}
		if (nop == true) {
			t.res --;
			printf("juega la maquina\n");
			showTablero(t);
			return;
		}
		TurnoM(t, s);

	}
}

int main () {
	Tablero t;
	InicioTablero(t);
	srand(getpid());
	bool seguir = true;
	void (*fptr)(Tablero&, bool&); //declaracion de puntero a funcion
	printf("Elija la dificultad : 0-facil , 1-humano, 2-imposible \n");
	int choice;
	scanf("%i",&choice);
	if (choice == 0) fptr = TurnoM;
	else if (choice == 1) fptr = hum;
	else fptr = juegoP;
	while (t.res > 0 && seguir == true)  {
		TurnoH(t, seguir);
		fptr(t, seguir);
	}
	if (t.res == 0) printf("Empate \n");
}