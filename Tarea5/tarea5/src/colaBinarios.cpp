/* 5031022 */

#include "../include/colaBinarios.h"

#include <stdio.h>

struct nodoCola {
	TBinario dato;
	nodoCola* ant;
};
struct _rep_colaBinarios {
	nodoCola* frente;
	nodoCola* final;
};

TColaBinarios crearColaBinarios() {
	TColaBinarios c = new _rep_colaBinarios;
	c -> frente = c -> final = NULL;
	return c;
}

TColaBinarios encolar(TBinario b, TColaBinarios c) {
	nodoCola* nuevo = new nodoCola;
	nuevo -> dato = b;
	nuevo -> ant = NULL;
	if (!estaVaciaColaBinarios(c)) {
		c -> final -> ant = nuevo;
	} else {
		c -> frente = nuevo;
	}
	c -> final = nuevo;
	return c;
}

TColaBinarios desencolar(TColaBinarios c) {
	if (!estaVaciaColaBinarios(c)) {
		nodoCola* aborrar = c -> frente;
		c -> frente = c -> frente -> ant;
		if (estaVaciaColaBinarios(c)) { c -> final = NULL; }
		delete aborrar;
	}
	return c;
}

void liberarColaBinarios(TColaBinarios c) {
	while (c -> frente != NULL) {
		desencolar(c);
	}
	delete c;
}

bool estaVaciaColaBinarios(TColaBinarios c) {
	return (c -> frente == NULL);
}

TBinario frente(TColaBinarios c) {
	return (c -> frente -> dato);
}
