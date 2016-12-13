#include "stdio.h"
#include "m_malloc.h"

int main(){
  int **x,i,j;

  x = m_malloc(sizeof(int)*2);

  for(i = 0; i < 2; i++)
    x[i] = m_malloc(sizeof(int)*2);

  for(i = 0; i < 2; i++)
    for(j = 0; j < 2; j++)
      x[i][j] = 0;

  for(i = 0; i < 2; i++){
    for(j = 0; j < 2; j++)
      printf("%d", x[i][j]);
    printf("\n");
    }

  return 0;
}
