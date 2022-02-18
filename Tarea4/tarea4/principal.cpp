/*
  Módulo principal de la tarea 3.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', un TLocalizador 'loc', un TBinario 'b',
un TIterador 'it', una TPila 'p' y una TColaBinarios 'q'.

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
libera la memoria asignada a 'cad', 'b' e 'it',
los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/binario.h"
#include "include/cadena.h"
#include "include/colaBinarios.h"
#include "include/info.h"
#include "include/iterador.h"
#include "include/pila.h"
#include "include/usoTads.h"
#include "include/utils.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256
#define MAX_PILA 10

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

  TPila p = crearPila(MAX_PILA);
  TColaBinarios q = crearColaBinarios();
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

      // nueva
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

      // nueva
    } else if (0 == strcmp(nom_comando, "cantidadEnIterador")) {
      printf("%u.\n", cantidadEnIterador(it));

      // nueva
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

      // nueva
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

      // nueva
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
      // nueva
    } else if (0 == strcmp(nom_comando, "tiempo_binarioBalanceado")) {
      nat n = leerNat(), iter = leerNat(), timeout = leerNat();
      assert(n > 0);
      printf("\n Construyendo el arreglo. \n");
      ArregloNats elems = new nat[n];
      for (nat i = 0; i < n; i++)
        elems[i] = i;

      printf(" Construyendo el árbol. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        binarioBalanceado(elems, n);
      tm = clock() - tm;

      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);

      delete[] elems;

      // nueva
    } else if (0 == strcmp(nom_comando, "tiempo_recorridaPorNiveles")) {
      nat raiz = leerNat(), iter = leerNat(), timeout = leerNat();
      printf("\n Construyendo el árbol. \n");
      TBinario a = crearBinario();
      a = insertarEnBinario(crearInfo(raiz, (double)raiz), a);
      for (nat i = 1; i < raiz; i++) {
        a = insertarEnBinario(crearInfo(raiz - i, (double)raiz), a);
        a = insertarEnBinario(crearInfo(raiz + i, (double)raiz), a);
      }
      printf(" Imprimiendo el árbol. \n");

      clock_t tm = clock();
      for (nat i = 1; i <= iter; i++)
        recorridaPorNiveles(a);
      tm = clock() - tm;

      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);

      printf(" Liberando el árbol. \n");
      liberarBinario(a);

    } else if (0 == strcmp(nom_comando, "tiempo_sumaUltimosPositivos")) {
      nat min = leerNat(), max = leerNat(), iter = leerNat(),
          timeout = leerNat();
      printf("\n Construyendo el árbol. \n");
      TBinario a = crearBinario();
      for (nat i = max; i > min; i--)
        a = insertarEnBinario(crearInfo(i, (double)i), a);
      printf(" Obteniendo suma ultimos positivos. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        sumaUltimosPositivos(i, a);
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);

      printf(" Liberando binario. \n");
      liberarBinario(a);

    } else if (0 == strcmp(nom_comando, "tiempo_esAvl")) {
      nat raiz = leerNat(), dosH = leerNat(), iter = leerNat(),
          timeout = leerNat();
      printf("\n Construyendo el árbol. \n");
      TBinario a = crearBinario();
      a = insSubArbol(raiz, dosH, a);
      printf(" Evaluando si es AVL. \n");

      clock_t tm = clock();
      for (nat i = 0; i < iter; i++)
        esAvl(a);
      tm = clock() - tm;
      float tiempo = ((float)tm) / CLOCKS_PER_SEC;
      // printf("%f \n", tiempo);
      if (tiempo > timeout)
        printf("ERROR, tiempo excedido: %.1f > %d \n", tiempo, timeout);

      printf(" Liberando binario. \n");
      liberarBinario(a);

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
  return 0;
} // main
