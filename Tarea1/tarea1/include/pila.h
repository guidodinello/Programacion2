/*
  Módulo de definición de 'TPila'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _PILA_H
#define _PILA_H

#include "utils.h"

// Representación de 'TPila'.
// Se debe definir en pila.cpp.
// struct _rep_pila;
// Declaración del tipo 'TPila'.
typedef struct _rep_pila *TPila;

/* Operaciones de TPila */

/*
  Devuelve un elemento de tipo 'TPila' vacío (sin elementos).
 */
TPila crearPila();

/*
  Devuelve 'true' si y solo si 'pila' no tiene elementos.
 */
bool esVaciaPila(TPila pila);

/*
  Si en 'pila' hay menos de MAX (definido en utils.h) elementos apila
  'nuevo' en 'pila'. En otro caso la operación no tiene efecto.
  Devuelve 'pila'.
 */
TPila apilar(info_t nuevo, TPila pila);

/*
  Devuelve el tope de 'pila'.
  Precondición: 'pila' tiene elementos.
 */
info_t cima(TPila pila);

/*
  Si 'pila' tiene elementos desapila el tope de 'pila'.
  En otro caso la operación no tiene efecto.
  Devuelve 'pila'.
 */
TPila desapilar(TPila pila);

#endif
