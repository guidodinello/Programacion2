#include "include/a.h"
#include "include/b.h"

#include <stdio.h>
#include <string.h>

int main() {
  char nom_comando[100];
  int cont_comandos = 0;
  bool salir = false;
  while (!salir) {
    cont_comandos++;
    printf("%u>", cont_comandos);
    scanf("%s", nom_comando);
    if (!strcmp(nom_comando, "Fin")) {
       salir = true;
       printf("Fin.\n");
     } 
    else if (!strcmp(nom_comando, "a")) {
      float base, altura;
      printf("base: ");
      scanf("%f", &base);
      printf("altura: ");
      scanf("%f", &altura);
      float area = a(base, altura);
      printf("area: %f \n", area);
    } else if (!strcmp(nom_comando, "b")) {
      char p1[100], p2[100], concat[100];
      printf("primera palabra: ");
      scanf("%s", p1);
      printf("segunda palabra: ");
      scanf("%s", p2);
      b(p1, p2, concat);
      printf("palabras concatenadas: %s \n", concat);
    }
  }
  return 0;
}

