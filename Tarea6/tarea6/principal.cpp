/*
  Módulo principal de la tarea 6.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', un TLocalizador 'loc', un TBinario 'b',
un TIterador 'it', una TPila 'p', una TColaBinarios 'q', un TAvl 'avl',
un TConjunto 'conj', una TColCadenas 'colCads', un TMapping 'map',
una TColaDePrioridad 'cp' y un TGrafo 'g'.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

Si un parámetro debe ser de tipo TInfo su formato cumple con lo descrito en
'infoATexto' del módulo 'info''.


El comando
Fin
termina el programa

El comando
# comentario
imprime comentario.

El comando
reiniciar
libera la memoria asignada a 'cad', 'b', 'it', 'p', 'cavl', 'avl', 'conj', 'cp',
'map' y 'g' y
los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/avl.h"
#include "include/binario.h"
#include "include/cadena.h"
#include "include/colCadenas.h"
#include "include/colaBinarios.h"
#include "include/colaDePrioridad.h"
#include "include/conjunto.h"
#include "include/grafo.h"
#include "include/info.h"
#include "include/iterador.h"
#include "include/mapping.h"
#include "include/pila.h"
#include "include/usoTads.h"
#include "include/utils.h"

#include <assert.h>
#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h> // para srand, rand
#include <string.h>
#include <time.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

#define MAX_PILA 10
#define MAX_CADS 10
#define MAX_CP 10
#define MAX_MAP 10
#define MAX_N 10
#define MAX_M 30

/*
  Lee y devuelve un TInfo desde la entrada estándar.
  Se asume que la antrada cumple con el formato descrito en 'infoATexto' del
  módulo 'info''.
 */
TInfo leerInfo() {
  char simbolo = leerChar();
  assert(simbolo == '(');
  nat natural = leerNat();
  simbolo = leerChar();
  assert(simbolo == ',');
  double real = leerDouble();
  simbolo = leerChar();
  assert(simbolo == ')');
  (void)simbolo;
  return crearInfo(natural, real);
} // leerInfo

/*
  Lee y devuelve una TCadena desde la entrada estándar.
  Se asume que en la entrada hay un espacio en blanco después de cada elemento.
 */
TCadena leerCadena() {
  nat n = leerNat();
  TCadena res = crearCadena();
  for (nat i = 1; i <= n; i++) {
    TInfo info = leerInfo();
    res = insertarAlFinal(info, res);
  }
  return res;
} // leerCadena

/* Inserta subárboles. */
TBinario insSubArbol(nat dato, nat inc, TBinario a) {
  a = insertarEnBinario(crearInfo(dato, (double)dato), a);
  if (inc > 1) {
    inc >>= 1; // inc = inc / 2;
    a = insSubArbol(dato - inc, inc, a);
    a = insSubArbol(dato + inc, inc, a);
  }
  return a;
} // insSubArbol

struct tArregloTope {
  ArregloNats datos;
  nat tope;
};
typedef struct tArregloTope TArregloTope;

/*
  Lee una secuencia ordenada de manera creciente estricta de nat desde la
  entrada estándar y las devuelve en un arreglo con tope.
  Primero lee la cantidad de elemntos.
  Después de cada elemento hay un espacio en blanco.
 */
TArregloTope leerArregloOrdenado() {
  nat n = leerNat();
  TArregloTope res;
  res.tope = n;
  if (n == 0) {
    res.datos = NULL;
  } else {
    res.datos = new nat[n];
    for (nat i = 0; i < n; i++)
      res.datos[i] = leerNat();
  }
  return res;
} // leerArregloOrdenado

bool estaOrdenadoArreglo(TArregloTope A) {
  nat pos = 1;
  while ((pos < A.tope) && (A.datos[pos - 1] < A.datos[pos]))
    pos++;
  return (0 == A.tope) || (pos == A.tope);
} // estaOrdenadoArreglo

/*
  Lee un iterador ordenado de manera creciente estricta.
 */
TIterador leerIteradorOrdenado() {
  TArregloTope arreglo = leerArregloOrdenado();
  assert(estaOrdenadoArreglo(arreglo));
  TIterador res = crearIterador();
  for (nat pos = 0; pos < arreglo.tope; pos++)
    res = agregarAIterador(arreglo.datos[pos], res);
  if (arreglo.tope > 0)
    delete[] arreglo.datos;
  res = reiniciarIterador(res);
  return res;
} // leerIteradorOrdenado

// programa principal
int main() {

  TGrafo g = crearGrafo(MAX_N, MAX_M);
  TColaDePrioridad cp = crearCP(MAX_CP);
  TMapping map = crearMap(MAX_MAP);
  TAvl avl = crearAvl();
  TConjunto conj = crearConjunto();
  TColCadenas colCads = crearColCadenas(MAX_CADS);
  TColaBinarios q = crearColaBinarios();
  TPila p = crearPila(MAX_PILA);
  TIterador it = crearIterador();
  TBinario b = crearBinario();
  TCadena cad = crearCadena();
  TLocalizador loc = inicioCadena(cad); // no válido porque cad es vacía

  char restoLinea[MAX_LINEA + 1];
  char nom_comando[MAX_PALABRA];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    leerChars(nom_comando);

    // procesar el comando
    if (0 == strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (0 == strcmp(nom_comando, "#")) {
      leerRestoLinea(restoLinea);
      printf("# %s.\n", restoLinea);

      // operaciones de grafo
    } else if (0 == strcmp(nom_comando, "cantidadVertices")) {
      printf("%d.\n", cantidadVertices(g));

    } else if (0 == strcmp(nom_comando, "hayMParejas")) {
      printf("%s.\n", hayMParejas(g) ? "Hay M parejas" : "NO hay M parejas");

    } else if (0 == strcmp(nom_comando, "hacerVecinos")) {
      nat v1 = leerNat(), v2 = leerNat();
      assert((1 <= v1) && (v1 <= cantidadVertices(g)));
      assert((1 <= v2) && (v2 <= cantidadVertices(g)));
      assert(v1 != v2);
      assert(!sonVecinos(v1, v2, g));
      assert(!hayMParejas(g));
      double d = leerDouble();
      assert(d >= 0);
      g = hacerVecinos(v1, v2, d, g);
      printf("Nuevos vecinos: %d %d %4.2f.\n", v1, v2, d);

    } else if (0 == strcmp(nom_comando, "sonVecinos")) {
      nat v1 = leerNat(), v2 = leerNat();
      assert((1 <= v1) && (v1 <= cantidadVertices(g)));
      assert((1 <= v2) && (v2 <= cantidadVertices(g)));
      printf("%s vecinos.\n", sonVecinos(v1, v2, g) ? "Son" : "NO son");

    } else if (0 == strcmp(nom_comando, "distancia")) {
      nat v1 = leerNat(), v2 = leerNat();
      assert((1 <= v1) && (v1 <= cantidadVertices(g)));
      assert((1 <= v2) && (v2 <= cantidadVertices(g)));
      assert(sonVecinos(v1, v2, g));
      printf("%.2lf\n", distancia(v1, v2, g));

    } else if (0 == strcmp(nom_comando, "vecinos")) {
      nat v = leerNat();
      assert((1 <= v) && (v <= cantidadVertices(g)));
      TIterador vs = vecinos(v, g);
      vs = reiniciarIterador(vs);
      while (estaDefinidaActual(vs)) {
        printf("%d ", actualEnIterador(vs));
        vs = avanzarIterador(vs);
      }
      printf("\n");
      liberarIterador(vs);

      // operaciones de map
    } else if (0 == strcmp(nom_comando, "asociarEnMap")) {
      assert(!estaLlenoMap(map));
      nat clave = leerNat();
      double valor = leerDouble();
      assert(!existeAsociacionEnMap(clave, map));
      map = asociarEnMap(clave, valor, map);
      printf("Establecida la asociación.\n");

    } else if (0 == strcmp(nom_comando, "desasociarEnMap")) {
      nat clave = leerNat();
      assert(existeAsociacionEnMap(clave, map));
      map = desasociarEnMap(clave, map);
      printf("Eliminada la asociación.\n");

    } else if (0 == strcmp(nom_comando, "existeAsociacionEnMap")) {
      nat clave = leerNat();
      printf("%s.\n", existeAsociacionEnMap(clave, map)
                          ? "Existe asociacion"
                          : "No existe asociacion");

    } else if (0 == strcmp(nom_comando, "valorEnMap")) {
      nat clave = leerNat();
      assert(existeAsociacionEnMap(clave, map));
      printf("%.2lf\n", valorEnMap(clave, map));

    } else if (0 == strcmp(nom_comando, "estaLlenoMap")) {
      printf("%s.\n", estaLlenoMap(map) ? "LLeno" : "No lleno");

      // operaciones de cp

    } else if (0 == strcmp(nom_comando, "insertarEnCP")) {
      nat elem = leerNat();
      double valor = leerDouble();
      assert((1 <= elem) && (elem <= rangoCP(cp)));
      assert(!estaEnCP(elem, cp));
      cp = insertarEnCP(elem, valor, cp);
      printf("Se insertó el elemento.\n");

    } else if (0 == strcmp(nom_comando, "actualizarEnCP")) {
      nat elem = leerNat();
      double valor = leerDouble();
      assert(estaEnCP(elem, cp));
      cp = actualizarEnCP(elem, valor, cp);
      printf("Se actualizó el valor.\n");

    } else if (0 == strcmp(nom_comando, "eliminarPrioritario")) {
      assert(!estaVaciaCP(cp));
      cp = eliminarPrioritario(cp);
      printf("Eliminado.\n");

    } else if (0 == strcmp(nom_comando, "prioritario")) {
      assert(!estaVaciaCP(cp));
      printf("%d\n", prioritario(cp));

    } else if (0 == strcmp(nom_comando, "estaVaciaCP")) {
      printf("%s.\n", estaVaciaCP(cp) ? "Vacia" : "No vacía");

    } else if (0 == strcmp(nom_comando, "rangoCP")) {
      printf("%d.\n", rangoCP(cp));

    } else if (0 == strcmp(nom_comando, "estaEnCP")) {
      nat elem = leerNat();
      printf("%s.\n", estaEnCP(elem, cp) ? "Está" : "No está");

    } else if (0 == strcmp(nom_comando, "prioridad")) {
      nat elem = leerNat();
      assert(estaEnCP(elem, cp));
      printf("%.2lf.\n", prioridad(elem, cp));

      // operaciones de avl
    } else if (0 == strcmp(nom_comando, "estaVacioAvl")) {
      printf("%s.\n", estaVacioAvl(avl) ? "Vacio" : "No vacío");

    } else if (0 == strcmp(nom_comando, "insertarEnAvl")) {
      nat elem = leerNat();
      assert(estaVacioAvl(buscarEnAvl(elem, avl)));
      avl = insertarEnAvl(elem, avl);
      printf("Insertado.\n");

    } else if (0 == strcmp(nom_comando, "buscarEnAvl")) {
      nat elem = leerNat();
      TAvl sub = buscarEnAvl(elem, avl);
      TBinario a2b = avlABinario(sub);
      imprimirBinario(a2b);
      liberarBinario(a2b);

    } else if (0 == strcmp(nom_comando, "raizAvl")) {
      assert(!estaVacioAvl(avl));
      printf("%d\n", raizAvl(avl));

    } else if (0 == strcmp(nom_comando, "izqAvl")) {
      assert(!estaVacioAvl(avl));
      TAvl subIzq = izqAvl(avl);
      if (estaVacioAvl(subIzq))
        printf("Izquierdo es vacío\n");
      else {
        printf("%d\n", raizAvl(subIzq));
      }

    } else if (0 == strcmp(nom_comando, "derAvl")) {
      assert(!estaVacioAvl(avl));
      TAvl subDer = derAvl(avl);
      if (estaVacioAvl(subDer))
        printf("Derecho es vacío\n");
      else {
        printf("%d\n", raizAvl(subDer));
      }

    } else if (0 == strcmp(nom_comando, "cantidadEnAvl")) {
      printf("Cantidad en avl: %d.\n", cantidadEnAvl(avl));

    } else if (0 == strcmp(nom_comando, "alturaDeAvl")) {
      printf("Altura de avl: %d.\n", alturaDeAvl(avl));

    } else if (0 == strcmp(nom_comando, "enOrdenAvl")) {
      TIterador itAvl = enOrdenAvl(avl);
      itAvl = reiniciarIterador(itAvl);
      if (!estaDefinidaActual(itAvl)) {
        printf("No hay elementos en el avl.\n");
      } else {
        do {
          printf("%d ", actualEnIterador(itAvl));
          itAvl = avanzarIterador(itAvl);
        } while (estaDefinidaActual(itAvl));
        printf("\n");
      }
      liberarIterador(itAvl);

    } else if (0 == strcmp(nom_comando, "arregloAAvl")) {
      TArregloTope elems = leerArregloOrdenado();
      liberarAvl(avl);
      if (elems.tope == 0)
        avl = crearAvl();
      else {
        avl = arregloAAvl(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TBinario a2b = avlABinario(avl);
      imprimirBinario(a2b);
      liberarBinario(a2b);

    } else if (0 == strcmp(nom_comando, "avlMin")) {
      nat h = leerNat();
      TAvl min = avlMin(h);
      TBinario a2b = avlABinario(min);
      imprimirBinario(a2b);
      liberarBinario(a2b);
      liberarAvl(min);

      // operaciones de conjunto

    } else if (0 == strcmp(nom_comando, "estaVacioConjunto")) {
      printf("%s.\n", estaVacioConjunto(conj) ? "Vacio" : "No vacío");

    } else if (0 == strcmp(nom_comando, "cardinalidad")) {
      printf("%d.\n", cardinalidad(conj));

    } else if (0 == strcmp(nom_comando, "perteneceAConjunto")) {
      nat elem = leerNat();
      printf("%s.\n",
             perteneceAConjunto(elem, conj) ? "Pertenece" : "No pertenece");

    } else if (0 == strcmp(nom_comando, "minimo")) {
      assert(!estaVacioConjunto(conj));
      printf("%s %d.\n", "mínimo: ", minimo(conj));

    } else if (0 == strcmp(nom_comando, "maximo")) {
      assert(!estaVacioConjunto(conj));
      printf("%s %d.\n", "máximo: ", maximo(conj));

    } else if (0 == strcmp(nom_comando, "singleton")) {
      nat elem = leerNat();
      liberarConjunto(conj);
      conj = singleton(elem);
      printf("Creado el singleton.\n");

    } else if (0 == strcmp(nom_comando, "arregloAConjunto")) {
      TArregloTope elems = leerArregloOrdenado();
      liberarConjunto(conj);
      if (elems.tope == 0)
        conj = crearConjunto();
      else {
        conj = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      printf("Arreglo a conjunto con %d elementos.\n", elems.tope);

    } else if (0 == strcmp(nom_comando, "unionDeConjuntos")) {
      TArregloTope elems = leerArregloOrdenado();
      TConjunto a;
      if (elems.tope == 0)
        a = crearConjunto();
      else {
        a = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TConjunto alias = conj;
      conj = unionDeConjuntos(alias, a);
      liberarConjunto(alias);
      liberarConjunto(a);
      printf("Union.\n");

    } else if (0 == strcmp(nom_comando, "diferenciaDeConjuntos")) {
      TArregloTope elems = leerArregloOrdenado();
      TConjunto a;
      if (elems.tope == 0)
        a = crearConjunto();
      else {
        a = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TConjunto alias = conj;
      conj = diferenciaDeConjuntos(alias, a);
      liberarConjunto(alias);
      liberarConjunto(a);
      printf("Diferencia.\n");

    } else if (0 == strcmp(nom_comando, "iteradorDeConjunto")) {
      TIterador itC = iteradorDeConjunto(conj);
      itC = reiniciarIterador(itC);
      if (!estaDefinidaActual(itC)) {
        printf("No hay elementos en el conjunto.\n");
      } else {
        do {
          printf("%d ", actualEnIterador(itC));
          itC = avanzarIterador(itC);
        } while (estaDefinidaActual(itC));
        printf("\n");
      }
      liberarIterador(itC);

      // operaciones de colCadenas
    } else if (0 == strcmp(nom_comando, "insertarEnColCadenas")) {
      TInfo info = leerInfo();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < MAX_CADS));
      colCads = insertarEnColCadenas(info, pos, colCads);
      printf("Se insertó %d en la cadena %d.\n", natInfo(info), pos);

    } else if (0 == strcmp(nom_comando, "estaEnColCadenas")) {
      nat dato = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < MAX_CADS));
      printf("%d %s en la cadena %d.\n", dato,
             (estaEnColCadenas(dato, pos, colCads)) ? "está" : "no está", pos);
    } else if (0 == strcmp(nom_comando, "infoEnColCadenas")) {
      nat dato = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < MAX_CADS));
      assert(estaEnColCadenas(dato, pos, colCads));
      TInfo info = infoEnColCadenas(dato, pos, colCads);
      ArregloChars txtInfo = infoATexto(info);
      printf("La primera aparición de %d en la cadena %d es %s\n", dato, pos,
             txtInfo);
      delete[] txtInfo;

    } else if (0 == strcmp(nom_comando, "removerDeColCadenas")) {
      nat dato = leerNat();
      nat pos = leerNat();
      assert((0 <= pos) && (pos < MAX_CADS));
      assert(estaEnColCadenas(dato, pos, colCads));
      colCads = removerDeColCadenas(dato, pos, colCads);
      printf("Se removió la primera aparición de %d de la cadena %d.\n", dato,
             pos);

      // operaciones de pila

    } else if (0 == strcmp(nom_comando, "apilar")) {
      if (estaLlenaPila(p))
        printf("p está llena.\n");
      else {
        nat num = leerNat();
        p = apilar(num, p);
        printf("Apilado.\n");
      }

    } else if (0 == strcmp(nom_comando, "cima")) {
      assert(!estaVaciaPila(p));
      printf("%d.\n", cima(p));

    } else if (0 == strcmp(nom_comando, "desapilar")) {
      if (estaVaciaPila(p))
        printf("p está vacía.\n");
      else {
        p = desapilar(p);
        printf("Desapilado.\n");
      }

    } else if (0 == strcmp(nom_comando, "estaVaciaPila")) {
      printf("p %s vacia.\n", estaVaciaPila(p) ? "está" : "NO está");

    } else if (0 == strcmp(nom_comando, "estaLlenaPila")) {
      printf("p %s llena.\n", estaLlenaPila(p) ? "está" : "NO está");

      // operaciones de colaBinario

    } else if (0 == strcmp(nom_comando, "encolar")) {
      nat elem = leerNat();
      TBinario sub = buscarSubarbol(elem, b);
      q = encolar(sub, q);
      printf("Encolado.\n");

    } else if (0 == strcmp(nom_comando, "frente")) {
      assert(!estaVaciaColaBinarios(q));
      TBinario f = frente(q);
      if (esVacioBinario(f))
        printf("Binario vacío.\n");
      else
        printf("%d\n", natInfo(raiz(f)));

    } else if (0 == strcmp(nom_comando, "desencolar")) {
      if (estaVaciaColaBinarios(q))
        printf("q está vacía.\n");
      else {
        q = desencolar(q);
        printf("Desencolado.\n");
      }

    } else if (0 == strcmp(nom_comando, "estaVaciaColaBinarios")) {
      printf("q %s vacia.\n", estaVaciaColaBinarios(q) ? "está" : "NO está");

      // operaciones de iterador

    } else if (0 == strcmp(nom_comando, "agregarAIterador")) {
      nat elem = leerNat();
      it = agregarAIterador(elem, it);
      printf("Agregando.\n");

    } else if (0 == strcmp(nom_comando, "reiniciarIterador")) {
      it = reiniciarIterador(it);
      printf("Reiniciado.\n");

    } else if (0 == strcmp(nom_comando, "avanzarIterador")) {
      it = avanzarIterador(it);
      printf("Avanzando.\n");

    } else if (0 == strcmp(nom_comando, "actualEnIterador")) {
      assert(estaDefinidaActual(it));
      printf("%d\n", actualEnIterador(it));

    } else if (0 == strcmp(nom_comando, "estaDefinidaActual")) {
      printf("Actual de it %s definida.\n",
             estaDefinidaActual(it) ? "está" : "NO está");

      // operaciones de binario

    } else if (0 == strcmp(nom_comando, "avlABinario")) {
      TBinario a2b = avlABinario(avl);
      imprimirBinario(a2b);
      liberarBinario(a2b);

    } else if (0 == strcmp(nom_comando, "binarioBalanceado")) {
      TArregloTope elems = leerArregloOrdenado();
      assert(estaOrdenadoArreglo(elems));
      assert(elems.tope > 0);
      liberarBinario(b);
      b = binarioBalanceado(elems.datos, elems.tope);
      delete[] elems.datos;
      printf("\n");

    } else if (0 == strcmp(nom_comando, "insertarEnBinario")) {
      TInfo info = leerInfo();
      assert(esVacioBinario(buscarSubarbol(natInfo(info), b)));
      b = insertarEnBinario(info, b);
      printf("Insertado.\n");

    } else if (0 == strcmp(nom_comando, "mayor")) {
      assert(!esVacioBinario(b));
      ArregloChars txtInfo = infoATexto(mayor(b));
      printf("%s\n", txtInfo);
      delete[] txtInfo;

    } else if (0 == strcmp(nom_comando, "removerMayor")) {
      assert(!esVacioBinario(b));
      TInfo info = mayor(b);
      b = removerMayor(b);
      liberarInfo(info);
      printf("Removido el mayor.\n");

    } else if (0 == strcmp(nom_comando, "removerDeBinario")) {
      nat elem = leerNat();
      assert(!esVacioBinario(buscarSubarbol(elem, b)));
      b = removerDeBinario(elem, b);
      printf("Removido.\n");

    } else if (0 == strcmp(nom_comando, "esVacioBinario")) {
      printf("%s.\n", esVacioBinario(b) ? "Vacio" : "No vacío");

    } else if (0 == strcmp(nom_comando, "esAvl")) {
      printf("%s.\n", esAvl(b) ? "AVL" : "No AVL");

    } else if (0 == strcmp(nom_comando, "raiz")) {
      assert(!esVacioBinario(b));
      TInfo info = raiz(b);
      ArregloChars txtInfo = infoATexto(info);
      printf("%s\n", txtInfo);
      delete[] txtInfo;

    } else if (0 == strcmp(nom_comando, "izquierdo")) {
      assert(!esVacioBinario(b));
      if (esVacioBinario(izquierdo(b)))
        printf("izquierdo de b es vacío.\n");
      else {
        TInfo info = raiz(izquierdo(b));
        ArregloChars txtInfo = infoATexto(info);
        printf("%s\n", txtInfo);
        delete[] txtInfo;
      }

    } else if (0 == strcmp(nom_comando, "derecho")) {
      assert(!esVacioBinario(b));
      if (esVacioBinario(derecho(b)))
        printf("derecho de b es vacío.\n");
      else {
        TInfo info = raiz(derecho(b));
        ArregloChars txtInfo = infoATexto(info);
        printf("%s\n", txtInfo);
        delete[] txtInfo;
      }

    } else if (0 == strcmp(nom_comando, "buscarSubarbol")) {
      nat elem = leerNat();
      TBinario sub = buscarSubarbol(elem, b);
      if (esVacioBinario(sub))
        printf("sub es vacío.\n");
      else {
        ArregloChars txtInfo = infoATexto(raiz(sub));
        printf("%s\n", txtInfo);
        delete[] txtInfo;
      }

    } else if (0 == strcmp(nom_comando, "alturaBinario")) {
      printf("%d.\n", alturaBinario(b));

    } else if (0 == strcmp(nom_comando, "cantidadBinario")) {
      printf("%d.\n", cantidadBinario(b));

    } else if (0 == strcmp(nom_comando, "sumaUltimosPositivos")) {
      nat ult = leerNat();
      printf("%4.2lf\n", sumaUltimosPositivos(ult, b));

    } else if (0 == strcmp(nom_comando, "linealizacion")) {
      TCadena lineal = linealizacion(b);
      imprimirCadena(lineal);
      liberarCadena(lineal);

    } else if (0 == strcmp(nom_comando, "menores")) {
      double clave = leerDouble();
      TBinario filtro = menores(clave, b);
      imprimirBinario(filtro);
      liberarBinario(filtro);

    } else if (0 == strcmp(nom_comando, "imprimirBinario")) {
      imprimirBinario(b);

      // operaciones de cadena

    } else if (0 == strcmp(nom_comando, "esLocalizador")) {
      printf("loc%s válido.\n", esLocalizador(loc) ? "" : " no");

    } else if (0 == strcmp(nom_comando, "esVaciaCadena")) {
      printf("cad%s.\n", esVaciaCadena(cad) ? " vacia" : " no vacia");

    } else if (0 == strcmp(nom_comando, "inicioCadena")) {
      loc = inicioCadena(cad);
      printf("loc al inicio.\n");

    } else if (0 == strcmp(nom_comando, "finalCadena")) {
      loc = finalCadena(cad);
      printf("loc al final.\n");

    } else if (0 == strcmp(nom_comando, "infoCadena")) {
      assert(localizadorEnCadena(loc, cad));
      ArregloChars txtInfo = infoATexto(infoCadena(loc, cad));
      printf("%s\n", txtInfo);
      delete[] txtInfo;

    } else if (0 == strcmp(nom_comando, "esFinalCadena")) {
      printf("loc%s es final de cad.\n", esFinalCadena(loc, cad) ? "" : " no");

    } else if (0 == strcmp(nom_comando, "esInicioCadena")) {
      printf("loc%s es incio de cad.\n", esInicioCadena(loc, cad) ? "" : " no");

    } else if (0 == strcmp(nom_comando, "siguiente")) {
      assert(localizadorEnCadena(loc, cad));
      loc = siguiente(loc, cad);
      printf("loc al siguiente.\n");

    } else if (0 == strcmp(nom_comando, "anterior")) {
      assert(localizadorEnCadena(loc, cad));
      loc = anterior(loc, cad);
      printf("loc al anterior.\n");

    } else if (0 == strcmp(nom_comando, "insertarAlFinal")) {
      cad = insertarAlFinal(leerInfo(), cad);
      printf("Insertado al final.\n");

    } else if (0 == strcmp(nom_comando, "insertarAntes")) {
      assert(localizadorEnCadena(loc, cad));
      cad = insertarAntes(leerInfo(), loc, cad);
      printf("Insertado antes de loc.\n");

    } else if (0 == strcmp(nom_comando, "removerDeCadena")) {
      assert(localizadorEnCadena(loc, cad));
      cad = removerDeCadena(loc, cad);
      printf("Removido.\n");

    } else if (0 == strcmp(nom_comando, "imprimirCadena")) {
      imprimirCadena(cad);

    } else if (0 == strcmp(nom_comando, "kesimo")) {
      nat k = leerNat();
      loc = kesimo(k, cad);
      if (esLocalizador(loc))
        printf("loc en la posición %d.\n", k);
      else
        printf("loc quedó no válido.\n");

    } else if (0 == strcmp(nom_comando, "localizadorEnCadena")) {
      printf("loc%s pertenece a cad.\n",
             localizadorEnCadena(loc, cad) ? "" : " no");

    } else if (0 == strcmp(nom_comando, "precedeEnCadena")) {
      printf("loc1%s precede a loc.\n",
             precedeEnCadena(kesimo(leerNat(), cad), loc, cad) ? "" : " no");

    } else if (0 == strcmp(nom_comando, "insertarSegmentoDespues")) {
      assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      cad = insertarSegmentoDespues(leerCadena(), loc, cad);
      printf("Segmento insertado después de loc.\n");

    } else if (0 == strcmp(nom_comando, "copiarSegmento")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert((1 <= k1) && (k1 <= k2));
      TLocalizador desde = kesimo(k1, cad), hasta = kesimo(k2, cad);
      assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
      TCadena sgm = copiarSegmento(desde, hasta, cad);
      imprimirCadena(sgm);
      liberarCadena(sgm);

    } else if (0 == strcmp(nom_comando, "borrarSegmento")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert((1 <= k1) && (k1 <= k2));
      TLocalizador desde = kesimo(k1, cad), hasta = kesimo(k2, cad);
      assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
      cad = borrarSegmento(desde, hasta, cad);
      printf("Segmento borrado.\n");

    } else if (0 == strcmp(nom_comando, "cambiarEnCadena")) {
      assert(localizadorEnCadena(loc, cad));
      TInfo anteriorInfo = infoCadena(loc, cad);
      cad = cambiarEnCadena(leerInfo(), loc, cad);
      liberarInfo(anteriorInfo);
      printf("Cambio.\n");

    } else if (0 == strcmp(nom_comando, "intercambiar")) {
      nat k1 = leerNat(), k2 = leerNat();
      assert((1 <= k1) && (1 <= k2));
      TLocalizador loc1 = kesimo(k1, cad), loc2 = kesimo(k2, cad);
      assert(localizadorEnCadena(loc1, cad) && localizadorEnCadena(loc2, cad));
      cad = intercambiar(loc1, loc2, cad);
      printf("Intercambio.\n");

    } else if (0 == strcmp(nom_comando, "siguienteClave")) {
      assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      int clave = leerNat();
      loc = siguienteClave(clave, loc, cad);
      if (esLocalizador(loc))
        printf("loc avanzó buscando %d.\n", clave);
      else
        printf("loc quedó no válido.\n");

    } else if (0 == strcmp(nom_comando, "anteriorClave")) {
      assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
      int clave = leerNat();
      loc = anteriorClave(clave, loc, cad);
      if (esLocalizador(loc))
        printf("loc retrocedió buscando %d.\n", clave);
      else
        printf("loc quedó no válido.\n");

    } else if (0 == strcmp(nom_comando, "menorEnCadena")) {
      assert(localizadorEnCadena(loc, cad));
      loc = menorEnCadena(loc, cad);
      printf("El menor es %d.\n", natInfo(infoCadena(loc, cad)));

      // operaciones de usoTads


    } else if (0 == strcmp(nom_comando, "interseccionDeConjuntos")) {
      TArregloTope elems = leerArregloOrdenado();
      TConjunto a;
      if (elems.tope == 0)
        a = crearConjunto();
      else {
        a = arregloAConjunto(elems.datos, elems.tope);
        delete[] elems.datos;
      }
      TConjunto alias = conj;
      conj = interseccionDeConjuntos(alias, a);
      liberarConjunto(alias);
      liberarConjunto(a);
      printf("Intersección.\n");

    } else if (0 == strcmp(nom_comando, "cantidadEnIterador")) {
      printf("%u.\n", cantidadEnIterador(it));

    } else if (0 == strcmp(nom_comando, "enAlguno")) {
      TIterador otro = leerIteradorOrdenado();
      TIterador res = enAlguno(it, otro);
      res = reiniciarIterador(res);
      while (estaDefinidaActual(res)) {
        printf("%u ", actualEnIterador(res));
        res = avanzarIterador(res);
      }
      printf("\n");
      liberarIterador(otro);
      liberarIterador(res);

    } else if (0 == strcmp(nom_comando, "soloEnA")) {
      TIterador otro = leerIteradorOrdenado();
      TIterador res = soloEnA(it, otro);
      res = reiniciarIterador(res);
      while (estaDefinidaActual(res)) {
        printf("%u ", actualEnIterador(res));
        res = avanzarIterador(res);
      }
      printf("\n");
      liberarIterador(otro);
      liberarIterador(res);

    } else if (0 == strcmp(nom_comando, "recorridaPorNiveles")) {
      TIterador niveles = recorridaPorNiveles(b);
      niveles = reiniciarIterador(niveles);
      while (estaDefinidaActual(niveles)) {
        nat actual = actualEnIterador(niveles);
        if (actual == UINT_MAX)
          printf("| ");
        else
          printf("%u ", actual);
        niveles = avanzarIterador(niveles);
      }
      printf("\n");
      liberarIterador(niveles);

    } else if (0 == strcmp(nom_comando, "esCamino")) {
      TCadena camino = leerCadena();
      printf("%s camino.\n", esCamino(camino, b) ? "Es" : "NO es");
      liberarCadena(camino);

    } else if (0 == strcmp(nom_comando, "nivelEnBinario")) {
      nat l = leerNat();
      if (l == 0) {
        printf("l = 0.\n");
      } else {
        TCadena nivel = nivelEnBinario(l, b);
        imprimirCadena(nivel);
        liberarCadena(nivel);
      }

    } else if (0 == strcmp(nom_comando, "pertenece")) {
      int i = leerNat();
      printf("%d%s pertenece a cad.\n", i, pertenece(i, cad) ? "" : " no");

    } else if (0 == strcmp(nom_comando, "longitud")) {
      printf("Longitud: %u\n", longitud(cad));

    } else if (0 == strcmp(nom_comando, "estaOrdenadaPorNaturales")) {
      printf("cad%s.\n",
             estaOrdenadaPorNaturales(cad) ? " ordenada" : " no ordenada");

    } else if (0 == strcmp(nom_comando, "hayNatsRepetidos")) {
      printf("En cad%s.\n", hayNatsRepetidos(cad)
                                ? " hay naturales repetidos"
                                : " no hay naturales repetidos");

    } else if (0 == strcmp(nom_comando, "sonIgualesCadena")) {
      TCadena otra = leerCadena();
      printf("%s.\n",
             sonIgualesCadena(cad, otra) ? "Son iguales" : "No son iguales");
      liberarCadena(otra);

    } else if (0 == strcmp(nom_comando, "concatenar")) {
      TCadena otra = leerCadena();
      TCadena conc = concatenar(cad, otra);
      imprimirCadena(conc);
      liberarCadena(conc);
      liberarCadena(otra);

    } else if (0 == strcmp(nom_comando, "ordenar")) {
      assert(!hayNatsRepetidos(cad));
      cad = ordenar(cad);
      printf("Quedó ordenada.\n");

    } else if (0 == strcmp(nom_comando, "cambiarTodos")) {
      nat original = leerNat(), nuevo = leerNat();
      cad = cambiarTodos(original, nuevo, cad);
      printf("Cambiados.\n");

    } else if (0 == strcmp(nom_comando, "subCadena")) {
      assert(estaOrdenadaPorNaturales(cad));
      nat menor = leerNat(), mayor = leerNat();
      assert(menor <= mayor);
      assert(pertenece(menor, cad) && pertenece(mayor, cad));
      TCadena sub = subCadena(menor, mayor, cad);
      imprimirCadena(sub);
      liberarCadena(sub);

      // test de tiempo
    } else if (0 == strcmp(nom_comando, "tiempo_grafo")) {
      nat tamanio = leerNat();
      TGrafo gt = crearGrafo(tamanio, 2 * tamanio);
      nat v = tamanio / 2;
      for (nat i = 1; i < v; i++)
        hacerVecinos(i, v, 10, gt);
      for (nat i = tamanio; i > v; i--)
        hacerVecinos(i, v, 10, gt);
      liberarGrafo(gt);
      printf("\n");

    } else if (0 == strcmp(nom_comando, "tiempo_map")) {
      nat tamanio = leerNat();
      const nat MODULO = 1000000;
      srand(1);
      TMapping a = crearMap(tamanio);
      printf("prueba asociar, desasociar, existeAsociacion. \n");
      for (nat j = 1; j < tamanio; j++) {
        nat rnd = rand() % MODULO;
        if (existeAsociacionEnMap(rnd, a))
          a = desasociarEnMap(rnd, a);
        a = asociarEnMap(rnd, (double)rnd, a);
      }
      printf("prueba existeAsociacion, valorEnMap. \n");
      for (nat j = 0; j < MODULO; j++) {
        nat rnd = rand() % MODULO;
        if (existeAsociacionEnMap(rnd, a))
          valorEnMap(rnd, a);
      }
      liberarMap(a);

    } else if (0 == strcmp(nom_comando, "tiempo_cp")) {
      nat N = leerNat();
      printf("\n prueba 1. \n");
      TColaDePrioridad a = crearCP(N);
      for (nat i = N; i >= 1; i--) {
        insertarEnCP(i, (double)i, a);
      }
      for (nat i = 1; i <= N; i++)
        eliminarPrioritario(a);
      liberarCP(a);

      printf(" prueba 2. \n");
      a = crearCP(N);
      for (nat i = 1; i <= N; i++) {
        insertarEnCP(i, (double)i, a);
      }
      for (nat i = 1; i <= N; i++)
        eliminarPrioritario(a);
      liberarCP(a);

      printf(" prueba 3. \n");
      a = crearCP(N);
      insertarEnCP(N, (double)N, a);
      for (nat i = 1; i <= N; i++) {
        insertarEnCP(1, 1.0, a);
        eliminarPrioritario(a);
        prioritario(a);
      }
      liberarCP(a);

      printf(" prueba 4. \n");
      a = crearCP(N);
      insertarEnCP(1, 1.0, a);
      insertarEnCP(N, (double)N, a);
      for (nat i = 1; i <= N; i++) {
        estaEnCP(1, a);
        estaEnCP(N / 2, a);
        estaEnCP(N, a);
      }
      liberarCP(a);

    } else if (0 == strcmp(nom_comando, "reiniciar")) {
      liberarCadena(cad);
      cad = crearCadena();
      loc = inicioCadena(cad);
      liberarBinario(b);
      b = crearBinario();
      liberarIterador(it);
      it = crearIterador();
      liberarPila(p);
      p = crearPila(MAX_PILA);
      liberarColaBinarios(q);
      q = crearColaBinarios();
      liberarAvl(avl);
      avl = crearAvl();
      liberarConjunto(conj);
      conj = crearConjunto();
      liberarColCadenas(colCads);
      colCads = crearColCadenas(MAX_CADS);
      liberarCP(cp);
      cp = crearCP(MAX_CP);
      liberarMap(map);
      map = crearMap(MAX_MAP);
      liberarGrafo(g);
      g = crearGrafo(MAX_N, MAX_M);
      printf("Estructuras reiniciadas.\n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while

  liberarCadena(cad);
  liberarIterador(it);
  liberarBinario(b);
  liberarPila(p);
  liberarColaBinarios(q);
  liberarAvl(avl);
  liberarConjunto(conj);
  liberarColCadenas(colCads);
  liberarCP(cp);
  liberarMap(map);
  liberarGrafo(g);
  return 0;
} // main
