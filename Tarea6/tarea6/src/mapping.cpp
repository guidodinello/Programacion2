/* 5031022 */

#include "../include/mapping.h"

#include <stdio.h>

struct nodoMap {
	nat dom;
	double codom;
	nodoMap* sig;
};
struct _rep_mapping { 
// hash, pues desasociar, valorEnMap O(1) en promedio
//, contador extra pus estaLlenoMap en O(1)
// asociar en O(1)
	nat actuales;
	nat tamanio;
	nodoMap** hash;
};

// O(m)
TMapping crearMap(nat M) {
	TMapping nuevo = new _rep_mapping;
	nuevo -> tamanio = M;
	nuevo -> actuales = 0;
	nuevo -> hash = new nodoMap*[M];
	for (nat m=0; m<M; m++) {
		nuevo -> hash[m] = NULL;
	}
	return nuevo;
}

static nat funcHash(nat param, nat divisor) {
	return (param % divisor);
}
// O(1)
TMapping asociarEnMap(nat clave, double valor, TMapping map) {
	nat pos = funcHash(clave, map -> tamanio);
	nodoMap* nuevo = new nodoMap;
	nuevo -> dom = clave;
	nuevo -> codom = valor;
	nuevo -> sig = map -> hash[pos];
	map -> hash[pos] = nuevo;
	map -> actuales ++;
	return map;
}

// O(1)
TMapping desasociarEnMap(nat clave, TMapping map) {
	nat pos = funcHash(clave, map -> tamanio);
	nodoMap* aborrar = map -> hash[pos];
	nodoMap* iter = aborrar;
	if (aborrar -> dom != clave) {
		aborrar = aborrar -> sig;
		while (aborrar -> dom != clave){
			aborrar = aborrar -> sig;
			iter = iter -> sig;
		}
		iter -> sig = aborrar -> sig;
	} else {
		map -> hash[pos] = aborrar -> sig;
	}
	delete aborrar;
	map -> actuales --;
	return map;
}

// O(1)
bool existeAsociacionEnMap(nat clave, TMapping map) {
	nat pos = funcHash(clave, map -> tamanio);
	nodoMap* iter = map -> hash[pos];
	while (iter != NULL && iter -> dom != clave) {
		iter = iter -> sig;
	}
	return (iter != NULL);
}

// O(1)
double valorEnMap(nat clave, TMapping map) {
	nat pos = funcHash(clave, map -> tamanio);
	nodoMap* iter = map -> hash[pos];
	while (iter -> dom != clave) {
		iter = iter -> sig;
	}
	return (iter -> codom);
}

// O(1)
bool estaLlenoMap(TMapping map) {
	return (map -> actuales == map -> tamanio);
}

// O(m)
void liberarMap(TMapping map) {
	for (nat m=0; m < map -> tamanio; m++) {
		nodoMap* aborrar;
		while (map -> hash[m] != NULL) {
			aborrar = map -> hash[m];
			map -> hash[m] = map -> hash[m] -> sig;
			delete aborrar;
		}	
	}
	delete [] map -> hash;
	delete map;
}
