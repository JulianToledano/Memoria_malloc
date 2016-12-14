#include "m_malloc.h"
#include "unistd.h"

void *base = NULL;

ptr_bloque buscar_bloque(ptr_bloque *ultimo, size_t m_tamano){
  // base es un puntero global al punto de comienzo del heap
  ptr_bloque aux = base;
  // Mientras haya bloques de memoria y este esté vacío y no
  while(aux && !(aux->libre && aux->tamano >= m_tamano)){
    *ultimo = aux;
    aux = aux->siguiente;
  }
  return aux;
}

ptr_bloque aumentar_heap(ptr_bloque ultimo, size_t m_tamano){
  int stack_base;
  ptr_bloque aux;
  // sbrk(0) es un caso especial que devuelve la dirección actual del break
  aux = sbrk(0);
  stack_base = (int)sbrk(TAMANO_BLOQUE + m_tamano);
  // Si sbrk() falla devolvemos NULL
  if(sbrk(TAMANO_BLOQUE + m_tamano) == (void*) - 1)
    return NULL;
  aux->tamano = m_tamano;
  aux->siguiente = NULL;
  aux->previo = ultimo;
  aux->ptr = aux->dato;
  if(ultimo)
    ultimo->siguiente = aux;
  aux->libre = 0;
  return aux;
}

void dividir_bloque(ptr_bloque a_dividir, size_t m_tamano){
  ptr_bloque nuevo;
  // Como dato es del tipo char[] la suma se realiza con precisión de byte
  nuevo = (ptr_bloque)(a_dividir->dato + m_tamano);
  nuevo->tamano = a_dividir->tamano - m_tamano - TAMANO_BLOQUE;
  nuevo->siguiente = a_dividir->siguiente;
  nuevo->previo = a_dividir;
  nuevo->libre = 1;
  nuevo->ptr = nuevo->dato;
  nuevo->tamano = m_tamano;
  nuevo->siguiente = nuevo;
  if(nuevo->siguiente)
    nuevo->siguiente->previo = nuevo;
}

void *m_malloc(size_t m_tamano){
  ptr_bloque aux, ultimo;
  size_t s;
  s = align4(m_tamano);
  // Si la base ha sido inicializada
  if(base){
    ultimo = base;
    aux = buscar_bloque(&ultimo, s);
    // Encontraos un bloque?
    if(aux){
      // Tratamos de dividirlo
      if((aux->tamano - s) >= (TAMANO_BLOQUE + 4))
        dividir_bloque(aux, s);
      aux->libre = 0;
    }
    // En caso de no encontrar un bloque, aumentamos el heap
    else{
      aux = aumentar_heap(ultimo, s);
      if(!aux)
        return NULL;
    }
  }
  // Si es la primera vez que se llama a malloc
  else{
    // Aumentamos el heap
    aux = aumentar_heap(NULL, s);
    if(!aux)
      return NULL;
    base = aux;
  }
  return (aux->dato);
}
