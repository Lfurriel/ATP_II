#include <stdio.h>

int main() {
  int matriz[5][5], i, j, count = 5;

  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      scanf("%d", &matriz[i][j]);
    }
  }
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (matriz[i][j] != matriz[j][i]) {
        printf("Matriz nao simetrica!");
        return 0;
      } 
    }
  }

  printf("Matriz simetrica!");
  return  0;
}