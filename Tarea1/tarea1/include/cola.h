/*
  Módulo de definición de 'TCola'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_H
#define _COLA_H

#include "utils.h"

// Representación de 'TCola'.
// Se debe definir en cola.cpp.
// struct _rep_cola;
// Declaración del tipo 'TCola'.
typedef struct _rep_cola *TCola;

/* Operaciones de TCola */

/*
  Devuelve un elemento de tipo 'TCola' vacío (sin elementos).
 */
TCola crearCola();

/*
  Devuelve 'true' si y solo si 'cola' no tiene elementos.
 */
bool esVaciaCola(TCola cola);

/*
  Si en 'cola' hay menos de MAX (definido en utils.h) elementos encola
  'nuevo' en 'cola'. En otro caso la operación no tiene efecto.
  Devuelve 'cola'.
 */
TCola encolar(info_t nuevo, TCola cola);

/*
  Devuelve el frente de 'cola'.
  Precondición: 'cola' tiene elementos.
 */
info_t frente(TCola cola);

/*
  Si 'cola' tiene elementos desapila el frente de 'cola'.
  En otro caso la operación no tiene efecto.
  Devuelve 'cola'.
 */
TCola desencolar(TCola c);

#endif
