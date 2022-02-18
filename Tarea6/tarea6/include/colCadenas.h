/*
  Módulo de definición de 'TColCadenas'.

  Un elemento de tipo 'TColCadenas' es una colección acotada de 'TCadena's.

  La cantidad de elementos que mantiene, M, se establece en el parámetro
  de 'crearColCadenas'.
  Cada cadena se identifica con una posición entre 0 y M - 1.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _COL_CADENAS_H
#define _COL_CADENAS_H

#include "info.h"

// Representación de 'TColCadenas'.
// Se debe definir en 'colCadenas.cpp'.
// struct _rep_colCadenas;
// Declaración del tipo 'TColCadenas'
typedef struct _rep_colCadenas *TColCadenas;

/*
  Devuleve una colección de 'M' cadenas vacías.
  Precondición: M > 0.
  El tiempo de ejecución en el peor caso es O(M).
 */
TColCadenas crearColCadenas(nat M);

/*
  Inserta 'info' al inicio de la cadena de 'col' identificada con 'pos'.
  El tiempo de ejecución en el peor caso es O(1).
  La inserción no se efectúa si 'pos >= M', siendo 'M' el parámetro 
  pasado en 'crearColCadenas'.
  Devuelve cad.
 */
TColCadenas insertarEnColCadenas(TInfo info, nat pos, TColCadenas col);

/*
  Devuelve 'true' si y solo si 'dato' es el componente natural de algún
  elemento de la cadena de 'col' identificada con 'pos'.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaEnColCadenas(nat dato, nat pos, TColCadenas col);

/*
  Devuelve el primer elemento (el más cercano al inicio) de la cadena de 'col'
  identificada con 'pos' cuyo componenete natural es 'dato'.
  Precondición: estaEnColCadenas(dato, pos, col)
  El tiempo de ejecución en el peor caso es O(1).
 */
TInfo infoEnColCadenas(nat dato, nat pos, TColCadenas col);

/*
  Remueve el primer elemento (el más cercano al inicio) de la cadena de 'col'
  identificada con 'pos' cuyo componenete natural es 'dato'.
  Precondición: estaEnColCadenas(dato, pos, col)
  El tiempo de ejecución en el peor caso es O(1).
  Devuleve cad.
 */
TColCadenas removerDeColCadenas(nat dato, nat pos, TColCadenas col);

/*
  Devuelve la memoria asignada a 'col' y todos sus elementos.
  El tiempo de ejecución es O(n), siendo 'n' la suma de ña cantidad de
  elementos en cada una de las cadenas de 'col'.
 */
void liberarColCadenas(TColCadenas col);

#endif
