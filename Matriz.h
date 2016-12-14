// Generará las matrices
#include <stdio.h>
// Número de filas y columnas
#define fil_col 2

// Genera las matrices y las guarda en un archivo .txt
void generar_matrices(){
  FILE *matriz;
  int i,j;
  matriz = fopen("Matriz.txt", "w");
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      fprintf(matriz, "%d ", 1);
    fprintf(matriz,"\n");
  }

  fprintf(matriz,"\n");

  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      fprintf(matriz, "%d ", 2);
    fprintf(matriz,"\n");
  }

  fclose(matriz);
}

// Lee el archivo .txt y rellena las matrices pasadas por referencia
void rellenar_matrices(int **matriz1, int **matriz2){
  FILE *f;
  int i,j;
  f = fopen("Matriz.txt", "r");
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      fscanf(f,"%d", &matriz1[i][j]);
  }
  for(i = 0; i < fil_col; i++){
    for(j = 0; j < fil_col; j++)
      fscanf(f,"%d", &matriz2[i][j]);
  }
  fclose(f);
}
