/* 5031022 */

#include "../include/cola.h"
#include "../include/lista.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>

struct _rep_cola {
  TLista lst;
};

TCola crearCola() {
  TCola resultado = new _rep_cola;
  resultado->lst = crearLista();
  return resultado;
}

bool esVaciaCola(TCola cola) {
  return longitud( cola->lst ) == 0;
}

TCola encolar(info_t nuevo, TCola cola) {
  cola->lst = insertar(longitud(cola->lst)+1,nuevo,cola->lst);
  return cola;
}

info_t frente(TCola cola) {
  assert(!esVaciaCola(cola));
  //devuelve el primer elemento de la cola
  return infoLista(1,cola->lst);
}

TCola desencolar(TCola cola) {
  cola->lst = remover(1,cola->lst);
  return cola;
}
