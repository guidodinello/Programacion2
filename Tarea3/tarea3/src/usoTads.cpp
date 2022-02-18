/* 5031022 */
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"
#include "../include/usoTads.h"
#include "../include/binario.h"

#include <stdio.h>

static void nivel(nat l, TBinario b, TCadena &c) {
	if (!esVacioBinario(b) && l>0) {
		nivel(l-1,izquierdo(b),c);
		if (l == 1) c = insertarAlFinal(copiaInfo(raiz(b)),c);
		else nivel(l-1,derecho(b),c);
	}
}
TCadena nivelEnBinario(nat l, TBinario b) {
	TCadena res = crearCadena();
	nivel(l,b,res);
	return res;
}

static bool esCam(TLocalizador aux,TCadena c, TBinario b) {
	if (!esVacioBinario(b) && esLocalizador(aux) && natInfo(raiz(b))==natInfo(infoCadena(aux,c))) {
		if (izquierdo(b)==NULL && derecho(b)==NULL && esFinalCadena(aux,c)) return true;
		else return (esCam(siguiente(aux,c),c,izquierdo(b))||esCam(siguiente(aux,c),c,derecho(b)));
	} else return false;
}
bool esCamino(TCadena c, TBinario b) {
	TLocalizador aux = inicioCadena(c);
	if (esVacioBinario(b) && !esLocalizador(aux)) return true;
	else return esCam(aux,c,b);
}

bool pertenece(nat elem, TCadena cad) {
  return (esLocalizador(siguienteClave(elem,inicioCadena(cad),cad)));
}

nat longitud(TCadena cad) {
  nat res = 0;
  TLocalizador aux = inicioCadena(cad);
  while (esLocalizador(aux)) {
    aux = siguiente(aux,cad);
    res += 1;
  }
  return res;
}

bool estaOrdenadaPorNaturales(TCadena cad) {
  TLocalizador aux = inicioCadena(cad);
  while (aux != finalCadena(cad) && natInfo(infoCadena(aux,cad)) <= natInfo(infoCadena(siguiente(aux,cad),cad))) {
    aux = siguiente(aux,cad);
  }
  return (aux == finalCadena(cad));
}

bool hayNatsRepetidos(TCadena cad) {
  //que debo devolver si la lista es Vacia?
  TLocalizador pivot = inicioCadena(cad);
  //capaz puedo usar un do-while para no entrar con repetidos ficticio
  bool repetidos = false;
  while (pivot != finalCadena(cad) && repetidos == false) {
    TLocalizador compara = siguiente(pivot,cad);
    while (esLocalizador(compara) && repetidos == false) {
      if (natInfo(infoCadena(pivot,cad)) == natInfo(infoCadena(compara,cad)))
        repetidos = true;
      compara = siguiente(compara,cad);
    }
    pivot = siguiente(pivot,cad);
  }
  return repetidos;
  // si la lista es vacia aca devuelvo false
}

bool sonIgualesCadena(TCadena c1, TCadena c2) {
  //que debo devolver si las listas tienen longitud distinta, supongo que false
  TLocalizador aux1 = inicioCadena(c1);
  TLocalizador aux2 = inicioCadena(c2);
  while (esLocalizador(aux1) && esLocalizador(aux2) && sonIgualesInfo(infoCadena(aux1,c1),infoCadena(aux2,c2))) {
    aux1 = siguiente(aux1,c1);
    aux2 = siguiente(aux2,c2);
  }
  return (aux1 == aux2);
  /* la unica forma que aux1 sea igual a aux2 es que ambos sean null, dado que tienen
  direcciones de memoria independiente, si aux1 != aux2 es porque una llego a null
  y la otra no ergo longitudes distintas ergo cadenasnoiguales, o porque las info
  eran distintas y luego cada uno apunta a su nodo de cadena correspondiente */
}

TCadena concatenar(TCadena c1, TCadena c2) {
  //debo precisar el insertarSegmentoDespues
  TCadena res = copiarSegmento(inicioCadena(c1),finalCadena(c1),c1);
  TCadena res2 = copiarSegmento(inicioCadena(c2),finalCadena(c2),c2);
  res = insertarSegmentoDespues(res2,finalCadena(res),res);
  //res = insertarSegmentoDespues(c2,finalCadena(res),res);
  //porque esta en cambio me daba violacion de segmento??
  return res;
}

TCadena ordenar(TCadena cad) {
  /*busca el menor en la subcadena siguiente aux y final, si es menor a
  aux lo cambia sino avanza aux, repite hasta aux final dado que el elemento final
  fue ordenado en el paso anterior  */
  TLocalizador aux = inicioCadena(cad);
  TLocalizador al_menor;
  while (aux != finalCadena(cad)) {
    al_menor = menorEnCadena(siguiente(aux,cad),cad);
    if (natInfo(infoCadena(aux,cad)) > natInfo(infoCadena(al_menor,cad)))
      intercambiar(aux,al_menor,cad);
    aux = siguiente(aux,cad);
  }
  return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
  //debo percisar el cambiarEnCadena, siguienteClave
  TLocalizador aux = siguienteClave(original,inicioCadena(cad),cad);
  while (esLocalizador(aux)) {
    TInfo cambio = crearInfo(nuevo,realInfo(infoCadena(aux,cad)));
    TInfo anterior_aux = infoCadena(aux,cad);
    cad = cambiarEnCadena(cambio, aux, cad);
    liberarInfo(anterior_aux);
    aux = siguienteClave(original,siguiente(aux,cad),cad);
  }
  return cad;
}

TCadena subCadena(nat menor, nat mayor, TCadena cad) {
  //debo precisar el copiaSegmento
  TLocalizador aux1 = inicioCadena(cad);
  TLocalizador aux2 = finalCadena(cad);
  while (natInfo(infoCadena(aux1,cad)) < menor)
    aux1 = siguiente(aux1,cad);
  while (natInfo(infoCadena(aux2,cad)) > mayor)
    aux2 = anterior(aux2,cad);
  TCadena sub = copiarSegmento(aux1,aux2,cad);
  return sub;
}

//no use borrarsegmento tal vez se usara en subcadena??
//no use precedeEnCadena, lo usan en principal??
