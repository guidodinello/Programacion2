/*
  Módulo principal de la tarea 1.

  Procesador de comandos que prueba las operaciones declaradas en los .h.

  Lee comandos desde la entrada estándar e imprime en la salida estándar.

  Cada comando ocupa una línea. Empieza con un nombre y opcionalmente tiene
  parámetros.

  El comando con nombre 'Fin' termina la ejecución del programa.
  El comando con nombre '#' representa un comentario.

  La entrada y salida se pueden redirigir a archivos.
  Un ejemplo de ejecución es
  $ ./principal < test/01.in > test/01.sal


  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#include "include/cola.h"
#include "include/mapping.h"
#include "include/pila.h"
#include "include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_PALABRA 32
#define MAX_LINEA 100

info_t leerInfo() {
  info_t res;
  scanf("%u %lf", &(res.natural), &(res.real));
  return res;
}

void imprimirInfo(info_t info) {
  printf("(%d,%.2lf)", info.natural, info.real);
}

// programa principal
int main() {

  TPila p = crearPila();
  TCola c = crearCola();
  TMapping m = crearMapping();

  char resto_linea[MAX_LINEA+1];

  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    // mostrar el prompt
    cont_comandos++;
    printf("%u>", cont_comandos);

    // leer el comando
    char nom_comando[MAX_PALABRA];
    scanf("%s", nom_comando);

    // procesar el comando
    if (0 == strcmp(nom_comando, "Fin")) {
      salir = true;
      printf("Fin.\n");
      // comentario
    } else if (0 == strcmp(nom_comando, "#")) {
      scanf("%[^\n]", resto_linea);
      printf("# %s.\n", resto_linea);

      // pila

    } else if (0 == strcmp(nom_comando, "esVaciaPila")) {
      if (esVaciaPila(p))
        printf("La pila está vacia. \n");
      else
        printf("La pila no está vacia. \n");

    } else if (0 == strcmp(nom_comando, "apilar")) {
      info_t nuevo = leerInfo();
      p = apilar(nuevo, p);
      printf("Apilar. \n");

    } else if (0 == strcmp(nom_comando, "cima")) {
      assert(!esVaciaPila(p));
      printf("La cima es ");
      imprimirInfo(cima(p));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "desapilar")) {
      p = desapilar(p);
      printf("Desapilar. \n");

      // cola

    } else if (0 == strcmp(nom_comando, "esVaciaCola")) {
      if (esVaciaCola(c))
        printf("La cola está vacia. \n");
      else
        printf("La cola no está vacia. \n");

    } else if (0 == strcmp(nom_comando, "encolar")) {
      info_t nuevo = leerInfo();
      c = encolar(nuevo, c);
      printf("Encolar. \n");

    } else if (0 == strcmp(nom_comando, "frente")) {
      assert(!esVaciaCola(c));
      printf("El frente es ");
      imprimirInfo(frente(c));
      printf("\n");

    } else if (0 == strcmp(nom_comando, "desencolar")) {
      c = desencolar(c);
      printf("Desencolar. \n");

      // mapping

    } else if (0 == strcmp(nom_comando, "esClave")) {
      nat clave;
      scanf("%ud", &clave);
      if (esClave(clave, m))
        printf("%d es clave. \n", clave);
      else
        printf("%d no es clave. \n", clave);

    } else if (0 == strcmp(nom_comando, "asociar")) {
      nat clave;
      double valor;
      scanf("%u %lf", &clave, &valor);
      m = asociar(clave, valor, m);
      printf("Asociar.\n");

    } else if (0 == strcmp(nom_comando, "valor")) {
      nat clave;
      scanf("%ud", &clave);
      assert(esClave(clave, m));
      printf("%d está asociado a %.2lf. \n", clave, valor(clave, m));

    } else if (0 == strcmp(nom_comando, "desasociar")) {
      nat clave;
      scanf("%ud", &clave);
      m = desasociar(clave, m);
      printf("Desasociar. \n");

    } else {
      printf("Comando no reconocido.\n");
    } // if
    fgets(resto_linea, MAX_LINEA + 1, stdin);
  } // while

  return 0;
}
