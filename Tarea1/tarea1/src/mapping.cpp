/* 5031022 */

#include "../include/mapping.h"
#include "../include/utils.h"
#include "../include/lista.h"

#include <assert.h>

struct _rep_mapping {
  TLista lst;
};

TMapping crearMapping(){
  TMapping resultado = new _rep_mapping;
  resultado->lst = crearLista();
  return resultado;
}

TMapping asociar(nat clave, double valor, TMapping map) {
  info_t nuevo;
  nuevo.natural = clave;
  nuevo.real = valor;
  if (!esClave(clave,map)) {
    map->lst = insertar(longitud(map->lst)+1,nuevo,map->lst);
  }
  return map;
}

bool esClave(nat clave, TMapping map) {
  return posNat(clave,map->lst);
}

double valor(nat clave, TMapping map) {
  return infoLista(posNat(clave,map->lst),map->lst).real;
}

TMapping desasociar(nat clave, TMapping map) {
  if (esClave(clave,map)) {
    map->lst = remover(posNat(clave,map->lst),map->lst);
  }
  return map;
}
