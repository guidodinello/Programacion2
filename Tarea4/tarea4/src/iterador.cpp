/* 5031022 */

#include "../include/iterador.h"

#include <stdio.h>

struct nodoiter {
	nat elem;
	nodoiter* sig;
};
struct _rep_iterador { 
	nodoiter *inicio, *fin, *actual;
	bool reinicio;
};

TIterador crearIterador() {
	TIterador it = new _rep_iterador;
	it -> inicio = it -> fin = it -> actual = NULL;
	it -> reinicio = false;
	return it;
}

TIterador agregarAIterador(nat elem, TIterador iter) {
	if (iter -> reinicio == false) {//no se reinicio
		nodoiter* nuevo = new nodoiter;
		nuevo -> elem = elem;
		nuevo -> sig = NULL;
		if (iter -> inicio == NULL)
			iter -> inicio = nuevo;
		else iter -> fin -> sig = nuevo;
		iter -> fin = nuevo;
	}
	return iter;
}

TIterador reiniciarIterador(TIterador iter) {
	if (iter -> inicio != NULL) //tiene elementos
		iter -> actual = iter -> inicio;
	iter -> reinicio = true;
	return iter;
}

TIterador avanzarIterador(TIterador iter) {
	if (estaDefinidaActual(iter))
		iter -> actual = iter -> actual -> sig;
	return iter;
}

nat actualEnIterador(TIterador iter) {
	return iter -> actual -> elem;
}

bool estaDefinidaActual(TIterador iter) {
	if (iter -> actual == NULL) return false;
	else return true;
}

void liberarIterador(TIterador iter) {
	nodoiter* aborr;
	while (iter -> inicio != NULL) {
		aborr = iter -> inicio;
		iter -> inicio = iter -> inicio -> sig;
		delete aborr;
	}
	delete iter;
}
