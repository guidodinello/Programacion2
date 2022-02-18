/* 5031022 */

#include "../include/avl.h"

#include <stdio.h>

struct _rep_avl {
	nat elem;
	nat altura, hijos;
	TAvl izq, der;
};

TAvl crearAvl() {
	return NULL;
}

bool estaVacioAvl(TAvl avl) {
	return (avl == NULL);
}

static nat max(nat n1, nat n2) {
	if (n1 > n2)
		return n1;
	else return n2;
}
static TAvl actualizarHij(TAvl avl) {
	int hijos = 0;
	if (avl -> izq != NULL) hijos = avl -> izq -> hijos + 1;
	if (avl -> der != NULL) hijos = hijos + avl -> der -> hijos + 1;
	avl -> hijos = hijos;
	return avl;
}
static TAvl actualizarAlt(TAvl avl) {
	avl -> altura = 1 + max(alturaDeAvl(avl -> izq), alturaDeAvl(avl -> der));
	return avl;
}
static TAvl rotacionSimpleIzq(TAvl l) {
	TAvl k = l -> izq;
	l -> izq = k -> der;
	k -> der = l;
	l = actualizarAlt(l);
	k = actualizarAlt(k);
	l = actualizarHij(l);
	k = actualizarHij(k);
	return k;
}
static TAvl rotacionSimpleDer(TAvl l) {
	TAvl k = l -> der;
	l -> der = k -> izq;
	k -> izq = l;
	l = actualizarAlt(l);
	k = actualizarAlt(k);
	l = actualizarHij(l);
	k = actualizarHij(k);
	return k;
}
static TAvl rotacionDobleIzq(TAvl avl) {
	avl -> izq = rotacionSimpleDer(avl -> izq);
	return rotacionSimpleIzq(avl);
}
static TAvl rotacionDobleDer(TAvl avl) {
	avl -> der = rotacionSimpleIzq(avl -> der);
	return rotacionSimpleDer(avl);
}
static TAvl balancear(TAvl avl) {
	if (int(alturaDeAvl(avl -> izq)) - int(alturaDeAvl(avl -> der)) == 2) { 
		if (alturaDeAvl(avl -> izq -> izq) >= alturaDeAvl(avl -> izq -> der))
			avl = rotacionSimpleIzq(avl);
		else avl = rotacionDobleIzq(avl);
	} 
	if (int(alturaDeAvl(avl -> der)) - int(alturaDeAvl(avl -> izq)) == 2) {
		if (alturaDeAvl(avl -> der -> der) >= alturaDeAvl(avl -> der -> izq))
			avl = rotacionSimpleDer(avl);
		else avl = rotacionDobleDer(avl);
	}
	return avl;
}
// O(log n)
TAvl insertarEnAvl(nat elem, TAvl avl) {
	if (avl == NULL) {
		TAvl nuevo = new _rep_avl;
		nuevo -> elem = elem;
		nuevo -> altura = 1;
		nuevo -> hijos = 0;
		nuevo -> izq = nuevo -> der = NULL;
		return nuevo;
	} else {
		if (elem > avl -> elem) {
			avl -> hijos ++;
			avl -> der = insertarEnAvl(elem, avl -> der);
		} else {
			avl -> hijos ++;
			avl -> izq = insertarEnAvl(elem, avl -> izq);
		}
		avl = balancear(avl);
		avl = actualizarAlt(avl);
	}
	return avl;
}

// O(log n)
TAvl buscarEnAvl(nat elem, TAvl avl) {
	while (avl != NULL && avl -> elem != elem) {
		if (avl -> elem > elem)
			avl = avl -> izq;
		else avl = avl -> der;
	}
	return avl;
}

nat raizAvl(TAvl avl) {
	return avl -> elem;
}

TAvl izqAvl(TAvl avl) {
	return avl -> izq;
}

TAvl derAvl(TAvl avl) {
	return avl -> der;
}

// O(1)
nat cantidadEnAvl(TAvl avl) {
	if (avl == NULL) return 0;
	else return 1 + avl -> hijos;
}

// O(1)
nat alturaDeAvl(TAvl avl) {
	if (avl == NULL) return 0;
	else return avl -> altura;
}


static void enOrdenaux(TIterador &a, TAvl b) {
	if (b != NULL) {
		enOrdenaux(a, b -> izq);
		a = agregarAIterador(b -> elem, a);
		enOrdenaux(a, b -> der);
	}
}
TIterador enOrdenAvl(TAvl avl) {
	TIterador res = crearIterador();
	if (avl != NULL) {	
		enOrdenaux(res, avl);
	}
	return res;
}

static TAvl ArregloAAvlAux(ArregloNats elems, int min, int max) {
	TAvl res = NULL;
	if (max >= min) {
		nat prom = (max + min)/2;
		res = new _rep_avl;
		res -> elem = elems[prom];
		res -> izq = ArregloAAvlAux(elems, min, prom -1);
		res -> der = ArregloAAvlAux(elems, prom +1, max);
		res = actualizarHij(res);
		res = actualizarAlt(res);
	}
	return res;
}
// O(n)
TAvl arregloAAvl(ArregloNats elems, nat n) {
	TAvl b = ArregloAAvlAux(elems, 0, n-1);
	return b;
}

static TAvl avlMinAux(int h, nat &nodo) {
	if (h <= 0) return NULL;
	else {
		TAvl subizq = avlMinAux(h-1, nodo);
		TAvl raiz = new _rep_avl;
		raiz -> elem = nodo;
		nodo ++;
		raiz -> izq = subizq;
		if (raiz -> izq == NULL) {
			raiz -> hijos = 0;
			raiz -> altura = 1;
		} else {
			raiz -> hijos = 1 + raiz -> izq -> hijos;
			raiz -> altura = 1 + raiz -> izq -> altura;
		}
		TAvl subder = avlMinAux(h-2, nodo);
		raiz -> der = subder;
		raiz = actualizarAlt(raiz);
		raiz = actualizarHij(raiz);
		return raiz;
	}
}
// O(n)
TAvl avlMin(nat h) {
	if (h == 0) return NULL;
	else  {
		nat e = 1;
		return  avlMinAux(h,e);
	}
}

void liberarAvl(TAvl avl) {
	if (avl != NULL) {
		liberarAvl(avl -> der);
		liberarAvl(avl -> izq);
		delete avl;
		avl = NULL;
	}
}