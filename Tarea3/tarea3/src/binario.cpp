/* 5031022 */

#include "../include/binario.h"

#include <stdio.h> //NULL

struct _rep_binario {
	TInfo elem;
	TBinario izq,der;
};

TBinario crearBinario() {
	TBinario b = NULL;
	return b;
}

TBinario insertarEnBinario(TInfo i, TBinario b) {
	if (b == NULL) {
		TBinario nuevo = new _rep_binario;
		nuevo -> der = nuevo -> izq = NULL;
		nuevo -> elem = i;
		return nuevo;
	}
	if (natInfo(i) > natInfo(b -> elem)) {
		b -> der = insertarEnBinario(i,b -> der);
	} else if (natInfo(i) < natInfo(b -> elem)) {
		b -> izq = insertarEnBinario(i,b -> izq);
	}
	return b;
}

TInfo mayor(TBinario b) { 
	while (b -> der != NULL)
		b = b -> der;
	return b -> elem;
}

TBinario removerMayor(TBinario b) {
	if (b -> der == NULL) {
		TBinario borrar = b;
		b = b -> izq;
		delete borrar;
	} else	b -> der = removerMayor(b -> der);
	return b;
}

TBinario removerDeBinario(nat elem, TBinario b) {
	if (b != NULL) {
		// no encontro sigue buscando
		if (elem > natInfo(b -> elem))
			b -> der = removerDeBinario(elem, b -> der);
		else if (elem < natInfo(b -> elem))
			b -> izq = removerDeBinario(elem, b -> izq);
		else if (elem == natInfo(b -> elem)) { //borra porque encontro
			TBinario aux = b;
			if (b -> izq == NULL) { //un hijo der
				b = b -> der;
				liberarInfo(aux -> elem);
				delete aux;
			} else if (b -> der == NULL) { //un hijo izq
				b = b -> izq;
				liberarInfo(aux -> elem);
				delete aux;
			} else {//dos hijos, hago el reemplazo
				liberarInfo(b -> elem);
				b -> elem = copiaInfo(mayor(b -> izq));
				b -> izq = removerDeBinario(natInfo(b -> elem), b -> izq);
			}
		}
	}
	return b;
}

void liberarBinario(TBinario b) {
	if (b != NULL) {
		liberarBinario(b -> izq);
		liberarBinario(b -> der);
		liberarInfo(b -> elem);
		delete b;
		b = NULL;
	}
}

bool esVacioBinario(TBinario b) {
	return (b == NULL);
}

static nat max(nat n1, nat n2) {
	if (n1 > n2) return n1;
	else return n2;
}
static int abs(int n1) {
	if (n1 >= 0) return n1;
	else return -n1;
}
static int balanceado(TBinario b) { 
//si estan balanceados los subarboles devuelve la altura sino devuelve -1 y para
//si no paro usa la altura devuelta para ver que el FE entre los subarboles sea <=1.
	if (b == NULL) return 0;
	int alt_izq = balanceado(b -> izq);
	if (alt_izq == -1) return -1;
	int alt_der = balanceado(b -> der);
	if (alt_der == -1) return -1;
	if (abs(alt_izq - alt_der) > 1) return -1;
	else return 1 + max(alt_izq,alt_der);
}
bool esAvl(TBinario b) {
	return (balanceado(b) != -1);
}

TInfo raiz(TBinario b) {
	return b -> elem;
}

TBinario izquierdo(TBinario b) {
	return b -> izq;
}

TBinario derecho(TBinario b) {
	return b -> der;
}

TBinario buscarSubarbol(nat elem, TBinario b) {
	while (b != NULL && natInfo(b -> elem) != elem) {
		if (natInfo(b -> elem) > elem)
			b = b -> izq;
		else b = b -> der;	
	}
	return b;
}

nat alturaBinario(TBinario b) {
	if (b == NULL) return 0;
	else return 1 + max(alturaBinario(b -> izq), alturaBinario(b -> der));
}

nat cantidadBinario(TBinario b) {
	if (b == NULL) return 0;
	else return (1 + cantidadBinario(b -> izq) + cantidadBinario(b -> der));
}

static double sup(nat i, TBinario b, int &cont) {
	if (b == NULL) return 0; //vacio no hace nada
	double suma_der = sup(i, b -> der, cont);
	if ((unsigned int)cont >= i) return suma_der; //se alcanzo los i luego no debe agregar raiz
	if (realInfo(b -> elem) > 0) {
		cont = cont + 1;		
		suma_der = suma_der + realInfo(b -> elem);
	}
	if ((unsigned int)cont >= i) return suma_der; //se alcanzo los i luego no debe buscar en izq
	double suma_izq = sup(i, b -> izq, cont);
	return suma_der + suma_izq; //i permitio buscar en izq y der luego debe sumar ambos
}
double sumaUltimosPositivos(nat i, TBinario b) {
	int contador = 0;
	double res = sup(i,b, contador);
	return res;
}

TCadena linealizacion(TBinario b) {
	TCadena cad = crearCadena();
	if (b != NULL) {
		cad = insertarSegmentoDespues(linealizacion(b->izq),finalCadena(cad),cad);
		cad = insertarAlFinal(copiaInfo(b -> elem), cad);
		cad = insertarSegmentoDespues(linealizacion(b->der),finalCadena(cad),cad);
	}
	return cad;
}

TBinario menores(double cota, TBinario b) {
	TBinario res;
	if (b == NULL) res = NULL;
	else {
		TBinario menor_izq = menores(cota,b -> izq);
		TBinario menor_der = menores(cota,b -> der);

		if (realInfo(b -> elem) < cota) {
			res = new _rep_binario;
			res -> izq = menor_izq;
			res -> der = menor_der;
			res -> elem = copiaInfo(b -> elem);
		} else if (menor_izq == NULL) {
			res = menor_der;
		} else if (menor_der == NULL) {
			res = menor_izq;
		} else {
			res = new _rep_binario;
			res -> elem = copiaInfo(mayor(menor_izq));
			res -> izq = menor_izq;
			res -> der = menor_der;
			removerMayor(menor_izq);
		}
	}	
	return res;
}

static void imp(TBinario b,int prof) {
	if (b != NULL) {
		imp(b -> der,prof+1);
		for (int i=0;i<prof;i++) 
			printf("-");
		ArregloChars i = infoATexto(b -> elem);	
		printf("%s", i);
		delete [] i;	
		printf("\n");
		imp(b -> izq,prof+1);
	}
}
void imprimirBinario(TBinario b) {
//n.logn el logn surge de encontrar el nodo y esto lo hace 
//para cada nodo por eso el n
//la prof la calcula mientras encuentra el nodo
	printf("\n");
	if (b != NULL) imp(b,0);
}



