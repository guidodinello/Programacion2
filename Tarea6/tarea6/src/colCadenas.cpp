/* 5031022 */

#include "../include/colCadenas.h"
#include "../include/cadena.h"

#include <stdio.h>

struct _rep_colCadenas {
	TCadena* elems;
	nat tamanio;
};

//O(M)
TColCadenas crearColCadenas(nat M) {
	TColCadenas col_cad = new _rep_colCadenas;
	col_cad -> elems = new TCadena[M];
	col_cad -> tamanio = M;
	for (nat i = 0; i < M; i ++)
		col_cad -> elems[i] = crearCadena();
	return col_cad;
}

// O(final=1)||O(antes=1) == O(1)
TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col) {//controlar pos < M
	if (pos < col -> tamanio) {
		if (esVaciaCadena(col -> elems[pos]))
			col -> elems[pos] = insertarAlFinal(info, col -> elems[pos]);
		else
			col -> elems[pos] = insertarAntes(info, inicioCadena(col -> elems[pos]), col -> elems[pos]);
	}	
	return col;
}

// O(sigclave=n) == O(n)
bool estaEnColCadenas(nat dato, nat pos, TColCadenas col) {
	return esLocalizador(siguienteClave(dato, inicioCadena(col -> elems[pos]), col -> elems[pos]));
}

// O(sigclave=n) == O(n)
TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col) {
	return infoCadena(siguienteClave(dato, inicioCadena(col -> elems[pos]), col-> elems[pos]), col -> elems[pos]);
}

// O(sigclave=n) == O(n)
TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col) {
//removerDeCadena(loc,cad) O(1)
//inicioCadena(cad) O(1)
//siguienteClave(nat,loc,cad) O(n)
	col -> elems[pos] = removerDeCadena(siguienteClave(dato, inicioCadena(col -> elems[pos]), col -> elems[pos]), col -> elems[pos]);
	return col;
}

void liberarColCadenas(TColCadenas col) {
	for (nat i=0; i < col -> tamanio; i++)
		liberarCadena(col -> elems[i]);
	delete [] col -> elems;
	delete col;
}

