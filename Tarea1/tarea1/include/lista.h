/*
  Módulo de definición de 'TLista'.

  Se definen las listas de elementos de tipo 'info_t'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _LISTA_H
#define _LISTA_H

#include "utils.h"

// Representación de 'TLista'.
// Se debe definir en lista.cpp.
// struct _rep_lista;
// Declaración del tipo 'TLista'.
typedef struct _rep_lista *TLista;

/* Operaciones de TLista */

/*
  Devuelve un elemento de tipo 'TLista' vacío (sin elementos).
 */
TLista crearLista();

/*
  Devuelve la cantidad de elementos de 'lista'.
 */
nat longitud(TLista lista);

/*
  Si longitud(lista) < MAX (definido en utils.h) y
  1 <= pos <= longitud(lista) + 1 inserta 'info' en la posición 'pos' de
  'lista'. En otro caso la operación no tiene efecto.
  Devuelve 'lista'.
 */
TLista insertar(nat pos, info_t info, TLista lista);

/*
  Si 1 <= pos <= longitud(lista) remueve de 'lista' el elemento que está en la
  posición 'pos'. En otro caso la operación no tiene efecto.
  Devuelve 'lista'.
 */
TLista remover(nat pos, TLista lista);

/*
  Devuelve la posición del primer elemento de 'lista' cuyo componente natural
  es igual a 'elem', o 0 si 'elem' no está en 'lista'.
 */
nat posNat(nat elem, TLista lista);

/*
  Devuelve el elementos que está en la posición 'pos' de 'lista'.
  Precondición 1 <= pos <= longitud(lista).
 */
info_t infoLista(nat pos, TLista lista);

#endif
