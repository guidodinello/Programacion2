/*
  Módulo de definición de TColaBinarios'.

  Los elementos de tipo 'TColaBinarios' son estructuras lineales con
  comportamiento FIFO cuyos elementos son de tipo 'TBinario' (que puede ser el
  árbol vacío).

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COLA_BINARIOS_H
#define _COLA_BINARIOS_H

#include "binario.h"
#include "utils.h"

// Representación de TColaBinarios'.
// Se debe definir en colaBinarios.cpp
// struct _rep_colaBinarios;
// Declaración del tipo 'TColaBinarios'
typedef struct _rep_colaBinarios *TColaBinarios;

/*
  Devuelve una 'TColaBinarios' vacía (sin elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaBinarios crearColaBinarios();

/*
  Encola 'b' en 'c'.
  Devuelve 'c'.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaBinarios encolar(TBinario b, TColaBinarios c);

/*
  Remueve de 'c' el elemento que está en el frente.
  Si estaVaciaColaBinarios(c) no hace nada.
  Devuelve 'c'.
  NO libera la memoria del elemento removido.
  El tiempo de ejecución en el peor caso es O(1).
 */
TColaBinarios desencolar(TColaBinarios c);

/*
  Libera la memoria asignada a 'c', pero NO la de sus elementos.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'c'.
 */
void liberarColaBinarios(TColaBinarios c);

/*
  Devuelve 'true' si y solo si 'c' es vacía (no tiene elementos).
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaVaciaColaBinarios(TColaBinarios c);

/*
  Devuelve el elemento que está en el frente de 'c'.
  Precondición: ! estaVaciaColaBinarios(c);
  El tiempo de ejecución en el peor caso es O(1).
 */
TBinario frente(TColaBinarios c);

#endif
