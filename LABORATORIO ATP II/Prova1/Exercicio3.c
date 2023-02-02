#include <stdio.h>
#include <stdlib.h>

int main() {
  int matrizMensal[12][4];
  float produto[4][2];
  int qntProd[12] = {0}, qtdAno[4] = {0}, totalAno = 0;
  float custoMes[12] = {0}, custoAno = 0, lucroMes[12] = {0}, lucroAno = 0;
  int i, j;

  for (i = 0; i < 12; i++) {
    for (j = 0; j < 4; j++) {
      matrizMensal[i][j] = rand() % 10;
      // scanf("%d", &matrizMensal[i][j]);
    }
  }
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      produto[i][j] = (rand() % 10) + 10;
      // scanf("%f", &produto[i][j]);
    }
  }

  for (i = 0; i < 12; i++) {
    for (j = 0; j < 4; j++) {
      printf("%d ", matrizMensal[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n");
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 2; j++) {
      printf("%.2f ", produto[i][j]);
    }
    printf("\n");
  }

  for (i = 0; i < 12; i++) {
    for (j = 0; j < 4; j++) {
      qntProd[i] += matrizMensal[i][j];
      qtdAno[j] += matrizMensal[i][j];
    }
  }

  printf("\n\nQuantidade produzida por mes:\n");
  for (i = 0; i < 12; i++) {
    printf("%d ", qntProd[i]);
  }
  printf("\n");
  printf("Quantidade produto por ano:\n");
  for (i = 0; i < 4; i++) {
    printf("%d ", qtdAno[i]);
  }
  printf("\n");
  printf("Quantidade produzida no ano:\n");
  for (i = 0; i < 4; i++) {
    totalAno+=qtdAno[i];
  }
  printf("%d\n", totalAno);

  for (i = 0; i < 12; i++) {
    for (j = 0; j < 4; j++) {
      custoMes[i] += produto[j][0] * matrizMensal[i][j];
      lucroMes[i] += produto[j][1] * matrizMensal[i][j];
    }
  }

  for(i = 0; i < 12; i++){
    custoAno += custoMes[i];
    lucroAno += lucroMes[i];
  }

  printf("\n");
  printf("Custo / Lucro mes:\n");
  for(i = 0; i < 12; i++){
    printf("%.2f ", custoMes[i]);
  }
  printf("\n");
  for(i = 0; i < 12; i++){
    printf("%.2f ", lucroMes[i]);
  }

  printf("\n\nCusto / Lucro ano:\n%.2f %.2f\n", custoAno, lucroAno);  
  
  return 0;
}