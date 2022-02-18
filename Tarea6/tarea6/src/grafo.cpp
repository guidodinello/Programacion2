/* 5031022 */

#include "../include/grafo.h"
#include "../include/avl.h" //los vecinos de un vertice pertenecen a su avl asociado
#include "../include/mapping.h" // la distancia se obtiene del hashing

#include <stdio.h>

struct mapeo {
	nat v1;
	nat v2;
	double distancia;
	mapeo *sig;
};
struct _rep_grafo {
	TAvl* vecinos; // es un arreglo de 0 a N con los vecinos de v organizados como AVL
	mapeo** terna; // no estoy seguro de como esta hecho este mapping
	nat aristas_tope;
	nat aristas_cota;
	nat vertices;
};

//-------------AUXILIAR-------------//

static nat min(nat v1, nat v2) {
	if (v1 > v2) return v2;
	else return v1;
}
static nat max(nat v1,nat v2) {
	if (v1 < v2) return v2;
	else return v1;
}
static nat funcHash(nat v1, nat v2, TGrafo g) {
//no estoy seguro del % que puse
	return ((min(v1,v2) - 1)*(g -> aristas_cota) + max(v1,v2) - 1) % g -> aristas_cota;
}
//----------------------------------//

// O(max {N,M}) N: nodos , M: cota para nro de aristas
TGrafo crearGrafo(nat N, nat M) {
	TGrafo nuevo = new _rep_grafo;
	nuevo -> vecinos = new TAvl[N + 1]; // i-celda guarda los vecinos del vertice i, 1<=i<=N
	nuevo -> terna = new mapeo*[M]; // key-celda guarda la terna arista (vi,vj,d) donde key = funcHash(arista)
	nuevo -> vertices = N; // nro de vertices
	nuevo -> aristas_cota = M; // aristas maximas posibles
	nuevo -> aristas_tope = 0; // aristas actuales
	for (nat n=0; n<=N; n++) {
		nuevo -> vecinos[n] = crearAvl();
	}
	for (nat m=0; m<M; m++) {
		nuevo -> terna[m] = NULL;
	}
	return nuevo;
}

// O(1)
nat cantidadVertices(TGrafo g) {
	return g -> vertices;
}

// O(1)
bool hayMParejas(TGrafo g) {
	return g -> aristas_tope == g -> aristas_cota;
}

// O(max{log n1, log n2})
TGrafo hacerVecinos(nat v1, nat v2, double d, TGrafo g) {
	g -> aristas_tope ++;
	g -> vecinos[v1] = insertarEnAvl(v2, g -> vecinos[v1]);
	g -> vecinos[v2] = insertarEnAvl(v1, g -> vecinos[v2]);

//aca empieza la duda
	nat clave = funcHash(v1, v2, g);
	if (g -> terna[clave]==NULL) {
		mapeo* nuevo = new mapeo;
		nuevo -> v1 = v1;
		nuevo -> v2 = v2;
		nuevo -> distancia = d;
		nuevo -> sig = NULL;
		g -> terna[clave] = nuevo;
	} else {
		mapeo* iter = g -> terna[clave];
		while (iter -> sig != NULL) {
			iter = iter -> sig;
		}
		mapeo* nuevo = new mapeo;
		nuevo -> sig = NULL;
		nuevo -> v1 = v1;
		nuevo -> v2 = v2;
		nuevo -> distancia = d;
		iter -> sig = nuevo;
	}
	return g;
//
}

// O(1)
bool sonVecinos(nat v1, nat v2, TGrafo g) {
	return buscarEnAvl(v1, g -> vecinos[v2]) != NULL;
}

// O(1)
double distancia(nat v1, nat v2, TGrafo g) {
	nat clave = funcHash(v1, v2, g);

//duda
	mapeo* iter = g -> terna[clave];
	while (iter -> sig != NULL && !(iter -> v1 == v1 && iter -> v2 == v2)) //si sig es null, luego solo hay una arista en la clave y es la que buscamos
		iter = iter -> sig;
	if (!(iter -> v1 == v1 && iter -> v2 == v2)) {
		iter = g -> terna[clave];
		while (!(iter -> v1 == v2 && iter -> v2 == v1))
			iter = iter -> sig;
	}
	return iter -> distancia;
}

// O(n)
TIterador vecinos(nat v, TGrafo g) {
	return enOrdenAvl(g -> vecinos[v]);
}

// O(n + m)
void liberarGrafo(TGrafo g) {
	for (nat n=0; n<=g -> vertices; n++)
		liberarAvl(g -> vecinos[n]);
//duda
	for (nat m=0; m<g -> aristas_cota; m++) {
		mapeo* iter = g -> terna[m];
		mapeo* a_borrar;
		while (iter != NULL) {
			a_borrar = iter;
			iter = iter -> sig;
			delete a_borrar;
		}
	}
//		
	delete [] g -> vecinos;
	delete [] g -> terna; 
	delete g;
}

