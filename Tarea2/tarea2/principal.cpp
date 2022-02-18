/*
  Módulo principal de la tarea 2.

Intérprete de comandos para probar los módulos.

Están creados una TCadena 'cad', un TLocalizador 'loc'.

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
libera la memoria asignada a 'cad',
'map' y 'g' y
los vuelve a crear.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/cadena.h"
#include "include/info.h"
#include "include/usoTads.h"
#include "include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_PALABRA 32
#define MAX_LINEA 256

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


// programa principal
int main() {

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



    } else if (0 == strcmp(nom_comando, "reiniciar")) {
      liberarCadena(cad);
      cad = crearCadena();
      loc = inicioCadena(cad);
      printf("Estructuras reiniciadas.\n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(restoLinea, MAX_LINEA + 1, stdin);
  } // while

  liberarCadena(cad);
  return 0;
} // main
