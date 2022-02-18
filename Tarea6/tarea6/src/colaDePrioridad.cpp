/* 5031022 */

#include "../include/colaDePrioridad.h"

#include <stdio.h>

struct elem {
	bool existe;
	double prioridad;
	nat pos; // da la posicion en el heap
};
struct _rep_colaDePrioridad {	// heap + arr.bool.
	elem* info;	// guarda la prioridad, existencia y posicion en el heap para cada clave
	nat* heap;	// son las claves ordenadas
	nat tope;	// cantidad de elementos actual
};

//-----------------AUXILIARES------------------//

static void swap(TColaDePrioridad &cp, nat n1, nat n2) { // O(1)
	//reordeno el heap
	cp -> heap[cp -> info[n1].pos] = n2;
	cp -> heap[cp -> info[n2].pos] = n1;
	//actualizo las posiciones
	nat aux = cp -> info[n1].pos;
	cp -> info[n1].pos = cp -> info[n2].pos;
	cp -> info[n2].pos = aux;
}

static void RestoreHeapUp(TColaDePrioridad &cp, nat nodo) {  // O(log n) 
	while ( cp -> info[nodo].pos > 1 &&
cp -> info[nodo].prioridad < 
cp -> info[cp -> heap[cp -> info[nodo].pos / 2]].prioridad
)
		swap(cp, nodo, cp -> heap[cp -> info[nodo].pos / 2]);

}

static void RestoreHeapDown(TColaDePrioridad &cp, nat nodo) {  // O(log n)
nat caso = 0;
bool existe_der = cp -> info[nodo].pos * 2 + 1 <= cp -> tope;
if (existe_der) {
	if (	cp -> info[nodo].prioridad >
		cp -> info[cp -> heap[cp -> info[nodo].pos * 2 + 1]].prioridad
	) caso = 2;
}
bool existe_izq = cp -> info[nodo].pos * 2 <= cp -> tope && cp -> info[nodo].pos * 2 > 0;
if (existe_izq) {
	if (	cp -> info[nodo].prioridad >
		cp -> info[cp -> heap[cp -> info[nodo].pos * 2]].prioridad
	) caso = 1;
}
if (existe_izq && existe_der) {
	if (	
	cp -> info[cp -> heap[cp -> info[nodo].pos * 2 + 1]].prioridad <
	cp -> info[cp -> heap[cp -> info[nodo].pos * 2]].prioridad
	) caso = 2;
	else caso = 1;
}
switch (caso) {
	case 1: // hijo izq prioritario
		swap(cp, nodo, cp -> heap[cp -> info[nodo].pos * 2]);
		RestoreHeapDown(cp, nodo);
		break;
	case 2: // hijo der prioritario
		swap(cp, nodo, cp -> heap[cp -> info[nodo].pos * 2 + 1]);
		RestoreHeapDown(cp, nodo);
		break;
	case 0: // no hace nada
		break;
	}
}

//---------------------------------------------//

// O(n)
TColaDePrioridad crearCP(nat N) {
	TColaDePrioridad nuevo = new _rep_colaDePrioridad;
	nuevo -> info = new elem[N+1];
	nuevo -> heap = new nat[N+1];
	nuevo -> heap[0] = N; //este sera el rango(valor maximo/capacidad)
	for (nat n=1; n<=N; n++) {
		nuevo -> info[n].existe = false;
	}
	nuevo -> tope = 0;
	return nuevo;
}


// O(1)
nat rangoCP(TColaDePrioridad cp) {
	return cp -> heap[0];
}

// O(log n)
TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
	cp -> heap[cp -> tope + 1] = elem;
	cp -> tope ++;
	cp -> info[elem].existe = true;
	cp -> info[elem].prioridad = valor;
	cp -> info[elem].pos = cp -> tope;
	// resta actualizar swapeando upwards
	RestoreHeapUp(cp, elem); 
	return cp;
}

// O(1)
bool estaVaciaCP(TColaDePrioridad cp) {
	return cp -> tope == 0;
}

// O(1)
nat prioritario(TColaDePrioridad cp) {
	return cp -> heap[1];
}

// O(log n)
TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp) {
	cp -> info[cp -> heap[1]].existe = false;
	cp -> heap[1] = cp -> heap[cp -> tope];
	cp -> info[cp -> heap[cp -> tope]].pos = 1;
	cp -> tope --;
	// resta actualizar swapeando downwards
	RestoreHeapDown(cp, cp -> heap[1]);
	return cp;
}

// O(1)
bool estaEnCP(nat elem, TColaDePrioridad cp) {
	return cp -> info[elem].existe;
}

// O(1)
double prioridad(nat elem, TColaDePrioridad cp) {
	return cp -> info[elem].prioridad;
}

// O(log n)
TColaDePrioridad actualizarEnCP(nat elem, double valor, TColaDePrioridad cp) { 
//debo actualizar el campo prioridad en info
//y luego debo reordenar el heap
	double viejo = cp -> info[elem].prioridad;
	cp -> info[elem].prioridad = valor;
	if (viejo < valor) {
		RestoreHeapDown(cp, elem);
	} else if (viejo > valor) {
		RestoreHeapUp(cp, elem);
	}
	return cp;
}

// O(n)
void liberarCP(TColaDePrioridad cp) {
	delete [] cp -> info;
	delete [] cp -> heap;
	delete cp;
}

