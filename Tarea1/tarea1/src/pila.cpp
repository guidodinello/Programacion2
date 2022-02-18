/* 5031022 */

#include "../include/pila.h"
#include "../include/lista.h"
#include "../include/utils.h"

#include <assert.h>

struct _rep_pila {
  TLista lst;
};

TPila crearPila() {
  // se obtiene memoria para la representacion de la pila
  TPila resultado = new _rep_pila;
  // (*resultado) es un registro de tipo _rep_pila
  // su unico campo es lst que debe ser inicializado
  (*resultado).lst = crearLista();
  return resultado;
}

bool esVaciaPila(TPila pila) {
  return longitud( (*pila).lst ) == 0;
}

TPila apilar(info_t nuevo, TPila pila) {
  pila->lst = insertar(longitud(pila->lst) +1,nuevo,pila->lst);
  return pila;
}

info_t cima(TPila pila) {
  assert(!esVaciaPila(pila));
  return infoLista(longitud(pila->lst),pila->lst);
}

TPila desapilar(TPila pila) {
  pila->lst = remover(longitud(pila->lst),pila->lst);
  return pila;
}
