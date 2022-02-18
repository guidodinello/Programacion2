/* 5031022 */

#include "../include/pila.h"

#include <stdio.h>

struct nodoPila {
	nat elem;
	nodoPila* sig;
};
struct _rep_pila {
	nat capacidad;
	nat actual;
	nodoPila* cima;
};

TPila crearPila(nat tamanio) {
	TPila p = new _rep_pila;
	p -> actual = 0;
	p -> cima = NULL;
	p -> capacidad = tamanio;
	return p;
}

TPila apilar(nat num, TPila p) {
	if (!estaLlenaPila(p)) {
		p -> actual = p -> actual + 1;
		nodoPila* nuevo = new nodoPila;
		nuevo -> elem = num;
		nuevo -> sig = p -> cima;
		p -> cima = nuevo;
	}
	return p;
}

TPila desapilar(TPila p) {
	if (!estaVaciaPila(p)) {
		p -> actual = p -> actual - 1;
		nodoPila* borra = p -> cima;
		p -> cima = p -> cima -> sig;
		delete borra;
	}
	return p;
}

void liberarPila(TPila p) {
	nodoPila* borra;
	while (p -> cima != NULL) {
		borra = p -> cima;
		p -> cima = p -> cima -> sig;
		delete borra;
	}
	p -> actual = 0;
	delete p;
}

bool estaVaciaPila(TPila p) {
	return (p -> cima == NULL);
}

bool estaLlenaPila(TPila p) {
	if (p -> actual == p -> capacidad) return true;
	else return false;
}

nat cima(TPila p) {
	return (p -> cima -> elem);
}