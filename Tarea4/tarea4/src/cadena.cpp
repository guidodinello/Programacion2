/* 5031022 */

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad) {
  TLocalizador a_borrar;
  while (cad -> inicio != NULL) {
    a_borrar = cad -> inicio;
    cad -> inicio = cad -> inicio -> siguiente;
    liberarInfo(a_borrar -> dato);
    delete a_borrar;
  }
  cad -> inicio = NULL;
  cad -> final = NULL;
  //para que los igualo a NULL si luego hago delete??
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
  //chequea solo inicio, final == NULL es redundante
  return (cad -> inicio == NULL);
}

TLocalizador inicioCadena(TCadena cad) {
  // versión que sigue la especificación
    TLocalizador res;
    if (esVaciaCadena(cad)) {
      res = NULL;
    } else {
      res = cad -> inicio;
    }
    return res;
}

TLocalizador finalCadena(TCadena cad) {
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else {
    res = cad -> final;
  }
  return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc,cad));
  return (loc -> dato);
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
  TLocalizador res = NULL;
  assert(localizadorEnCadena(loc,cad));
  if (!esFinalCadena(loc,cad))
    res = loc -> siguiente;
  return res;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  TLocalizador res = NULL;
  assert(localizadorEnCadena(loc,cad));
  if (!esInicioCadena(loc,cad))
    res = loc -> anterior;
  return res;
  // loc -> anterior es NULL si es el Inicio??
  //si es precondicion loc en cadena luego loc no null luego
  //cad inicio no null luego loc anterior no daria error
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad)) {
    return false;
  } else {
    return (loc == finalCadena(cad));
  }
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad)) {
    return false;
  } else {
    return (loc == inicioCadena(cad));
  }
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  TLocalizador nuevo = new nodoCadena;
  nuevo -> dato = i;
  if (esVaciaCadena(cad)) {
    cad -> inicio = nuevo;
    nuevo -> anterior = NULL;
  } else {
    nuevo -> anterior = finalCadena(cad);
    finalCadena(cad) -> siguiente = nuevo;
  }
  nuevo -> siguiente = NULL;
  cad -> final = nuevo;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  TLocalizador nuevo = new nodoCadena;
  nuevo -> dato = i;
  //assert(localizadorEnCadena(loc,cad));
  if (loc == inicioCadena(cad)) {
    nuevo -> anterior = NULL;
    cad -> inicio = nuevo;
  } else {
    anterior(loc,cad) -> siguiente = nuevo;
    nuevo -> anterior = anterior(loc,cad);
  }
  loc -> anterior = nuevo;
  nuevo -> siguiente = loc;
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  //assert(localizadorEnCadena(loc,cad));
  if (loc -> anterior == NULL) {
    cad -> inicio = loc -> siguiente;
  } else {
    loc -> anterior -> siguiente = loc -> siguiente;
  }
  if (loc -> siguiente == NULL) {
    cad -> final = loc -> anterior;
  } else {
    loc -> siguiente -> anterior = loc -> anterior;
  }
  liberarInfo(loc -> dato);
  delete loc;
  return cad;
}

void imprimirCadena(TCadena cad) {
  //ver si conviene rehacerla con infoatexto
  /*TLocalizador aux;
  aux = inicioCadena(cad);
  while (aux != NULL) {
    printf("(%u,%.2f)",natInfo(aux -> dato),realInfo(aux -> dato));
    aux = aux -> siguiente;
  }
  printf("\n");*/
  TLocalizador aux;
  aux = inicioCadena(cad);
  while (aux != NULL) {
    ArregloChars i = infoATexto(aux -> dato);
    printf("%s",i);
    delete [] i;
    aux = aux -> siguiente;
  }
  printf("\n");
}

TLocalizador kesimo(nat k, TCadena cad) {
  TLocalizador aux;
  aux = NULL;
  nat n = 1;
  if (k != 0) {
    aux = inicioCadena(cad);
    while (aux != NULL && n != k){
      aux = aux -> siguiente;
      n = n + 1;
    }
  }
  return aux;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  if (!esVaciaCadena(sgm)) {
    if (esVaciaCadena(cad)) {
      cad -> inicio = sgm -> inicio;
      cad -> final = sgm -> final;
    } else {
      if (loc == finalCadena(cad)) {
      //  loc -> siguiente = sgm -> inicio;
      //  sgm -> inicio -> anterior = loc;
        cad -> final = sgm -> final;
      } else {
      //  sgm -> inicio -> anterior = loc;
        sgm -> final -> siguiente = loc -> siguiente;
        loc -> siguiente -> anterior = sgm -> final;
      //  loc -> siguiente = sgm -> inicio;
      }
      sgm -> inicio -> anterior = loc;
      loc -> siguiente = sgm -> inicio;
    }
  }
  delete sgm;
  return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TCadena copia = crearCadena();
  if (!esVaciaCadena(cad)) {
    insertarAlFinal(copiaInfo(desde -> dato), copia);//si no es vacia siempre copia desde
    while (desde != hasta) {//si desde=hasta no hace nada sino avanza y copia
      desde = desde -> siguiente;
      insertarAlFinal(copiaInfo(desde -> dato), copia);
    }
  }
  return copia;
}

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  /* usando removerDeCadena, como imagino deberia ser */
  if (!esVaciaCadena(cad)) {
    if (desde == hasta) { // borra 1 solo
       removerDeCadena(desde,cad);
    } else {
       TLocalizador borra;
       while (desde != hasta) { //borra entre desde y hasta -1
         borra = desde;
         desde = desde -> siguiente;
         removerDeCadena(borra,cad);
       }
       removerDeCadena(hasta,cad); //borra hasta
    }
  }
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  loc -> dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  TInfo aux;
  aux = loc1 -> dato;
  loc1 -> dato = loc2 -> dato;
  loc2 -> dato = aux;
  return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador aux;
  if (!esVaciaCadena(cad) && esLocalizador(loc)) {
    aux = inicioCadena(cad);
    while (aux != NULL && !sonIgualesInfo(loc -> dato,aux -> dato))
      aux = aux -> siguiente;
    return (aux != NULL);
  } else {
    return false;
  }
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  if (!esVaciaCadena(cad) && esLocalizador(loc1) && esLocalizador(loc2)) {
    while (loc1 != NULL && loc1 != loc2)
      loc1 = loc1 -> siguiente;
    return (loc1 == loc2);
  } else {
    return false;}
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  if (!esVaciaCadena(cad)) {
    while (loc != NULL && natInfo(loc -> dato) != clave)
      loc = loc -> siguiente;
  }
  return loc;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  if (!esVaciaCadena(cad)) {
    while (loc != NULL && natInfo(loc -> dato) != clave)
      loc = loc -> anterior;
  }
  return loc;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador res = loc;
  while (loc != NULL) {
    if (natInfo(loc -> dato) < natInfo(res -> dato))
      res = loc;
    loc = loc -> siguiente;
  }
  return res;
}
