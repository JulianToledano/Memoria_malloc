#include "stdio.h"
#include "m_malloc.h"
#include "Matriz.h"

int main(){
  generar_matrices();
  int **matriz1,**matriz2, **resultado,i,j,k;

  // Guardamos espacio para las matrices
  matriz1 = m_malloc(sizeof(int*)* fil_col);
  matriz2 = m_malloc(sizeof(int*)* fil_col);
  resultado = m_malloc(sizeof(int*)* fil_col);

  for(i = 0; i < fil_col; i++){
    matriz1[i] = m_malloc(sizeof(int)*fil_col);
    matriz2[i] = m_malloc(sizeof(int)*fil_col);
    resultado[i] = m_malloc(sizeof(int)*fil_col);
  }

  rellenar_matrices(matriz1,matriz2);

  // Imprimimos las dos primeras matrices
  printf("Matriz 1:\n");
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      printf("%d ", matriz1[i][j]);
    printf("\n");
  }
  printf("\n");

  printf("Matriz 2:\n");
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      printf("%d ", matriz2[i][j]);
    printf("\n");
  }

  // Multiplicacion
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++){
      resultado[i][j] = 0;
      for(k = 0; k < fil_col; k++)
        resultado[i][j] += matriz1[i][k] * matriz2[k][j];
    }
  }

  // Imprimimos el resultado
  printf("Resultado:\n");
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      printf("%d ", resultado[i][j]);
    printf("\n");
  }

  // Liberamos la memoria
  for(i = 0; i < fil_col; i++){
    free(matriz1[i]);
    free(matriz2[i]);
    free(resultado[i]);
  }
  free(matriz1);
  free(matriz2);
  free(resultado);

  return 0;
}
