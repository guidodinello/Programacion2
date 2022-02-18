/*
  Módulo de definición de 'usoTads'.

  Se definen funciones sobre tads.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#ifndef _USOTADS_H
#define _USOTADS_H

#include "binario.h"
#include "cadena.h"
#include "conjunto.h"
#include "grafo.h"
#include "iterador.h"
#include "utils.h"

/*
  Devuelve un 'TConjunto' con los elementos que pertenecen a 'c1' y 'c2'.
  El 'TConjunto' resultado no comparte memoria ni con 'c1' no con 'c2'.
  El tiempo de ejecucion en el peor caso es O(n1 + n2 + n.log n),
  siendo 'n1' y 'n2' la cantidad de elementos de 'c1' y 'c2' respectivamente y
  'n' la del 'TConjunto' resultado.
 */
TConjunto interseccionDeConjuntos(TConjunto c1, TConjunto c2);

/*
  Devuelve la cantidad de elementos de 'it'.
  La posición actual de 'it' queda indefinida.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'it'.
 */
nat cantidadEnIterador(TIterador it);

/*
  Devuelve un TIterador con los elementos que están en 'a' o en 'b'.
  En una recorrida del iterador devuelto los elementos aparecerían en orden
  creciente estricto (no habrá elementos repetidos; si un elemento está en
  'a' y en 'b' se agrega solo una vez).
  La posiciones actual de 'a' y de 'b' quedan indefinidas.
  Precondición: en recorridas de 'a' o de 'b' los elementos aparecerían en
  orden creciente estricto (no hay elementos repetidos).
  El tiempo de ejecución en el peor caso es O(na + nb), siendo 'na' y 'nb' la
  cantidad de elementos de 'a' y 'b' respectivamente.
 */
TIterador enAlguno(TIterador a, TIterador b);

/*
  Devuelve un TIterador con los elementos que están en 'a' pero no en 'b'.
  En una recorrida del iterador devuelto los elementos aparecerían en orden
  creciente estricto (no habrá elementos repetidos).
  La posiciones actual de 'a' y de 'b' quedan indefinidas.
  Precondición: en recorridas de 'a' o de 'b' los elementos aparecerían en
  orden creciente estricto (no hay elemenotos repetidos).
  El tiempo de ejecución en el peor caso es O(na + nb), siendo 'na' y 'nb' la
  cantidad de elementos de 'a' y 'b' respectivamente.
 */
TIterador soloEnA(TIterador a, TIterador b);

/*
  Devuelve un TIterador con los componentes naturales de los elementos de
  cada nivel de 'b'.
  En la recorrida del TIterador resultado se encuentran primero los elementos
  que están en el nivel más profundo y al final el que corresponde a la raíz.
  Los elementos de cada nivel se encuentra en orden creciente (de izquierda a
  derecha).
  Para indicar el cambio de nivel se usa el valor UINT_MAX que se puede asumir
  que no es el componenete natural de ningún elemento de 'b'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'b'.

  Por ejemplo para el árbol (solo se muestran los componentes naturales)

       5
     /   \
    2     8
        /
       6

   la recorrida del TIterador resultado debe encontrar los siguientes valores
   en ese orden:

   6 UINT_MAX 2 8 UINT_MAX 5

  Ver más ejemplos en el caso 06.
 */
TIterador recorridaPorNiveles(TBinario b);

/*
  Devuelve una 'TCadena' con los elementos del nivel 'l' de 'b'.
  La raíz es el nivel 1.
  La 'TCadena' resultado debe estar ordenada de manera creciente según los
  componentes naturales de sus elementos.
  Precondición: l > 0.
  La 'TCadena' devuelta no comparte memoria con 'b'.
 */
TCadena nivelEnBinario(nat l, TBinario b);

/*
  Devuelve 'true' si y solo si en 'b' hay un camino desde la raiz hasta una
  hoja que sea compatible con 'c'.
  Decimos que una cadena y un camino son compatibles si tienen la misma
  longitud y al recorrer la cadena desde el inicio hasta el final y el camino
  desde la raíz hasta la hoja los componentes naturales de los respectivos
  elementos son iguales.
  Ver ejemplos en la letra.
  Si 'b' y 'c' son vacíos devuelve 'true'.
  El tiempo de ejecución es O(log n) en promedio, siendo 'n' es la cantidad de
  elementos de 'b'.
 */
bool esCamino(TCadena c, TBinario b);

/*
  Devuelve 'true' si y solo si en 'cad' hay un elemento cuyo campo natural es
  'elem'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool pertenece(nat elem, TCadena cad);

/*
  Devuelve la cantidad de elementos de 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
nat longitud(TCadena cad);

/*
  Devuelve 'true' si y solo si 'cad' está ordenada de forma no dereciente
  (creciente de manera no estricta) según las campos naturales de sus elementos.
  Si esVaciaVadena(cad) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool estaOrdenadaPorNaturales(TCadena cad);

/*
  Devuelve 'true' si y solo si los componentes naturales de algún par de
  elementos de 'cad' son iguales.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
bool hayNatsRepetidos(TCadena cad);

/*
  Devuelve 'true' si y solo si 'c1' y 'c2' son iguales (es decir, si los
  elementos son iguales y en el mismo orden).
  Si esVaciaCadena(c1) y esVaciaCadena(c2) devuelve 'true'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
bool sonIgualesCadena(TCadena c1, TCadena c2);

/*
  Devuelve el resultado de concatenar 'c2' después de 'c1'.
  La 'TCadena' resultado no comparte memoria ni con 'c1' ni con 'c2'.
  El tiempo de ejecución en el peor caso es O(n1 + n2), siendo 'n1' u 'n2' la
  cantidad de elementos de 'c1' y 'c2' respectivamente.
 */
TCadena concatenar(TCadena c1, TCadena c2);

/*
  Se ordena 'cad' de manera creciente según los componentes naturales de sus
  elementos.
  Devuelve 'cad'
  Precondición: ! hayNatsRepetidos(cad)
  No se debe obtener ni devolver memoria de manera dinámica.
  Se debe mantener las relaciones de precedencia entre localizadores.
  Si esVaciaCadena(cad) no hace nada.
  El tiempo de ejecución en el peor caso es O(n^2), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena ordenar(TCadena cad);

/*
  Cambia todas las ocurrencias de 'original' por 'nuevo' en los elementos
  de 'cad'.
  Devuelve 'cad'
  No debe quedar memoria inaccesible.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena cambiarTodos(nat original, nat nuevo, TCadena cad);

/*
  Devuelve la 'TCadena' de elementos de 'cad' que cumplen
  "menor <= natInfo (elemento) <= mayor".
  El orden relativo de los elementos en la 'TCadena' resultado debe ser el mismo
  que en 'cad'.
  Precondición: estaOrdenadaPorNaturales (cad), 'menor' <= 'mayor',
  pertenece (menor, cad), pertenece (mayor, cad).
  La 'TCadena' resultado no comparte memoria con 'cad'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad de
  elementos de 'cad'.
 */
TCadena subCadena(nat menor, nat mayor, TCadena cad);

#endif
