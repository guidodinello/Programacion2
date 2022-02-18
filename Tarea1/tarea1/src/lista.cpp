/*
  Módulo de implementación de 'TLista'.


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

/*
  Se incluyen los archivos en donde se declaran las operaciones y tipos que se
  deben implentar.
 */
#include "../include/lista.h"
#include "../include/utils.h"

// Biblioteca estándar
#include <assert.h>
//#include <stdlib.h>

/*
 Se define la representación declarada en lista.h
 Es un arrglo con tope,
 En C los índices de los arreglos empiezan en 0.
 Aquí no se va a usar la celda 0 por lo cual el tamaño del arreglo debe ser MAX
 + 1. Los elementos de la lista están entre 1 y 'longitud'.
*/
struct _rep_lista {
  nat longitud;
  info_t infos[MAX + 1];
};

/*
  Se obtiene un bloque de memoria para alojar el struct repLista.
  res es una referencia al bloque de memoria donde se aloja el registro.
  (*res) es la desreferencia de res: es el contenido referenciado por res.
 */
TLista crearLista() {
  TLista res = new _rep_lista;
  (*res).longitud = 0;
  return res;
}

nat longitud(TLista lista) { return (*lista).longitud; }

TLista insertar(nat pos, info_t info, TLista lista) {
  if ((longitud(lista) < MAX) && (1 <= pos) && (pos <= longitud(lista) + 1)) {
    (*lista).longitud++;
    for (nat i = (*lista).longitud; i > pos; i--)
      (*lista).infos[i] = (*lista).infos[i - 1];
    (*lista).infos[pos] = info;
  }
  return lista;
}

TLista remover(nat pos, TLista lista) {
  if ((1 <= pos) && (pos <= longitud(lista))) {
    for (nat i = pos; i < (*lista).longitud; i++)
      (*lista).infos[i] = (*lista).infos[i + 1];
    (*lista).longitud--;
  }
  return lista;
}

nat posNat(nat elem, TLista lista) {
  nat pos = 1;
  while ((pos <= (*lista).longitud) && ((*lista).infos[pos].natural != elem))
    pos++;
  if (pos <= (*lista).longitud)
    return pos;
  else
    return 0;  
  // Una alternativa a lo anterior es usar el operador ternario  
  // Si la condición se cumple el operador ternario '?' devuelve pos; en otro
  // caso devuelve 0.
//  return ((pos <= (*lista).longitud) ? pos : 0);
}

/*
  Con la macro assert se comprueba que se cumple la precondición.
  Al terminar la etapa de desarrollo, se agrega la directiva -DNDEBUG en las
  opciones del compilador para que las llamadas a assert no sean incluidas en el
  código objeto.
 */
info_t infoLista(nat pos, TLista lista) {
  assert((1 <= pos) && (pos <= longitud(lista)));
  return (*lista).infos[pos];
}
