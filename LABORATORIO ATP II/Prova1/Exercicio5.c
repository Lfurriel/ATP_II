#include <stdio.h>

int main() {
  int vet[18], i, j, aux, matriz[3][6];

  for (i = 0; i < 18; i++) {
    //vet[i] = i;
    scanf("%d", &vet[i]);
  }
  aux = 0;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 6; j++) {
      matriz[i][j] = vet[aux];
      aux++;
    }
  }

  printf("\n");
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 6; j++) {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }

  return 0;
}