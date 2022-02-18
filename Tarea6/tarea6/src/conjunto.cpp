/* 5031022 */

#include "../include/conjunto.h"
#include "../include/avl.h" //incluido por mi
#include "../include/usoTads.h" //es aceptable segun letra tarea5

#include <stdio.h>
#include <limits.h>

struct _rep_conjunto {
	TAvl conj;
	nat max, min;
//tal vezdeberia hacerlos punteros a nat si la union de un vacio me genera
//problema
};
//O(1)
TConjunto crearConjunto() { 
	TConjunto res = new _rep_conjunto;
	res -> conj = NULL;
	res -> max = UINT_MAX;
//podria poner 0 incluso pues si el conjunto
//es vacio no se puede preguntar ni por max ni por min
	res -> min = 0;
//tal vez seria mejor min=uintmax y max=0, dependiendo de cuando ordene
	return res;
}
//O(1)
TConjunto singleton(nat elem) {
	TConjunto res = crearConjunto();
	res -> conj = insertarEnAvl(elem, res -> conj); 
	res -> max = res -> min = elem;
	return res;
}

//O(c1+c2) eq O(res)
TConjunto unionDeConjuntos(TConjunto c1, TConjunto c2) {
//podria hacer iterador de conjunto con c1 y c2 ==> O(max {c1,c2})
//luego usar enAlguno de uso Tads ==> O(c1 + c2)
//y finalmente construir el... 
//NO PORQUE NO PODRIA CONSTRUIR EL AVL A PARTIR DE LOS ITERADORES
//PERO SI ME DEFINIERA UNA ESTRUCTURA AUXILIAR TAL VEZ PODRIA PASAR EL IT
//ERADOR A ARREGLO 
//Y DE ARREGLO A AVL ==> O(n)

	TIterador it_c1 = iteradorDeConjunto(c1); //O(c1)
	TIterador it_c2 = iteradorDeConjunto(c2); //O(c2)
	TIterador it_res = enAlguno(it_c1, it_c2); //O(c1+c2=res)
	liberarIterador(it_c1);
	liberarIterador(it_c2);
	nat cant = cantidadEnIterador(it_res); //O(res)
	TConjunto res;
	if (cant == 0) {
		liberarIterador(it_res);
		return res = crearConjunto();
	}
	ArregloNats res_arr = new nat[cant];
	it_res = reiniciarIterador(it_res); //O(1)
	nat pos = 0;
	while (estaDefinidaActual(it_res)) { //O(res)
		res_arr[pos] = actualEnIterador(it_res);
		it_res = avanzarIterador(it_res);
		pos ++;	
	}
	res = arregloAConjunto(res_arr, cant); //O(res) 
	liberarIterador(it_res);
	delete [] res_arr;
	return res;
}
//O(c1+c2)
TConjunto diferenciaDeConjuntos(TConjunto c1, TConjunto c2) {
	TIterador it_c1 = iteradorDeConjunto(c1); //O(c1)
	TIterador it_c2 = iteradorDeConjunto(c2); //O(c2)
	TIterador it_res = soloEnA(it_c1, it_c2); //O(c1+c2=res)
	liberarIterador(it_c1);
	liberarIterador(it_c2);
	nat cant = cantidadEnIterador(it_res); //O(res)
	TConjunto res;
	if (cant == 0) {
		liberarIterador(it_res);
		return res = crearConjunto();
	}
	ArregloNats res_arr = new nat[cant];
	it_res = reiniciarIterador(it_res); //O(1)
	nat pos = 0;
	while (estaDefinidaActual(it_res)) { //O(res)
		res_arr[pos] = actualEnIterador(it_res);
		it_res = avanzarIterador(it_res);
		pos ++;	
	}
	res = arregloAConjunto(res_arr, cant); //O(res) 
	liberarIterador(it_res);
	delete [] res_arr;
	return res;
}
//O(log n)
bool perteneceAConjunto(nat elem, TConjunto c) {
	return !estaVacioAvl(buscarEnAvl(elem, c -> conj));
}
//O(1)
bool estaVacioConjunto(TConjunto c) {
	return estaVacioAvl(c -> conj);
}
//O(1)
nat cardinalidad(TConjunto c) {
	return cantidadEnAvl(c -> conj);
}
//O(1)
nat minimo(TConjunto c) {
	return c -> min;
}
//O(1)
nat maximo(TConjunto c) {
	return c -> max;
}
//O(n)
TConjunto arregloAConjunto(ArregloNats elems, nat n) {
	TConjunto res = crearConjunto(); 
	res -> conj = arregloAAvl(elems, n);
	res -> max = elems[n-1];
	res -> min = elems[0];
	return res;
}
//O(n)
TIterador iteradorDeConjunto(TConjunto c) {
	TIterador res = enOrdenAvl(c -> conj);
	return res;
}
//O(n)
void liberarConjunto(TConjunto c) {
	liberarAvl(c -> conj);
	delete c;
}