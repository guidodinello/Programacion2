/*
  Módulo de definición de 'TMapping'.

  'TMapping' es un mapping de asociaciones de elementos de
   tipo nat con elementos de tipo double.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _MAPPING_H
#define _MAPPING_H

#include "utils.h"

// Representación de 'TMapping'.
// Se debe definir en mapping.cpp.
// struct _rep_mapping;
// Declaración del tipo 'TMapping'.
typedef struct _rep_mapping *TMapping;

/*  Operaciones de TMapping */

/*
  Devuelve un elemento de tipo 'TMapping' vacío (sin elementos).
 */
TMapping crearMapping();

/*
  Si en 'map' hay menos de MAX (definido en utils.h) asociaciones y 'clave'
  no tiene un valor asociado en 'map' agrega en 'map' la asociación
  (clave,valor). En otro caso la operación no tiene efecto.
  Devuelve 'map'.
 */
TMapping asociar(nat clave, double valor, TMapping map);

/*
  Devuelve 'true' si y solo si 'clave' tiene un valor asociado en 'map'.
 */
bool esClave(nat clave, TMapping map);

/*
  Devuelve el valor que en 'map' está asociado a 'clave'.
  Precondición: esClave(clave, map)
 */
double valor(nat clave, TMapping map);

/*
  Si 'clave' tiene un valor asociado en 'map' remueve de `map' la asociación de
  'clave'. En otro caso la operación no tiene efecto.
  Devuelve 'map'.
 */
TMapping desasociar(nat clave, TMapping map);

#endif
