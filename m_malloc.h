#include "unistd.h"

// La memoria debe de estar alineada.
#define align4(x) (((((x)-1)>>2)<<2)+4)
// Definimos el tamaño del bloque.
#define TAMANO_BLOQUE 20

// Realizamos un typedef ya que solo utilizaremos punteros
// así la sintaxis es más sencilla.
typedef struct bloque *ptr_bloque;

/*
 Necesitamos una pequeña estructura para
 guardar los metadatos de las reservas de memoria
    tamano    -> Tamaño del dato del bloque
    siguiente -> Puntero al siguiente bloque
    previo    -> Puntero al bloque anterior
    libre     -> Flag para marcar si está libre
    ptr       -> Puntero que apunta a dato
    dato      -> Indica el final de los metadatos, útil a la hora de dividir las celdas de memoria
*/
struct bloque{
  size_t tamano;
  struct bloque *siguiente;
  struct bloque *previo;
  int libre;
  void *ptr;
  char dato[1];
};

/*
 Fitst fit malloc:
    -> Recorremos la lista de bloques
    -> Hasta encontrar un bloque libre con el tamaño suficiente
*/

// Función para encontrar un bloque de memoria válido.
// Empezamos en la dirección base del heap y vamos comprobando
// hasta encontrar el adecuado.
ptr_bloque buscar_bloque(ptr_bloque *ultimo, size_t m_tamano);

// Función para aumentar el tamaño del heap:
//    1º Movemos el break
//    2º Inicializamod un nuevo bloque
//    3º Actualizamos los campos del ultimo bloque de la lista
// Devuelve NULL si sbrk falla.
ptr_bloque aumentar_heap(ptr_bloque ultimo, size_t m_tamano);

// Esta función divide el tamaño del bloque pasado por argumento
// para hacer un nuevo bloque del tamaño especificado. Como en otras funciones
// m_tamano ya está alineado.
void dividir_bloque(ptr_bloque a_dividir, size_t m_tamano);

/*
 Función m_malloc:
      1º Alineamos el tamaño requerido
      2º Si la base está inicializada:
              Si encontramo un bloque:
                  -> Tratamos de dividirlo
                  -> Marcar el blque como ocupado
              En otro caso:
                  -> Expandimos el heap
        En otro caso:
              -> Expandimos el heap
*/
void *m_malloc(size_t m_tamano);
