#include <stdio.h>

void vencedor(int, int, int, int, int, int);

int main() {

  float c1 = 0, c2 = 0, c3 = 0, c4 = 0, b = 0, n = 0, total = 0;
  int voto;
    
  do {
    scanf("%d", &voto);
    switch (voto) {
    case 1:
      c1++;
      total++;
      break;

    case 2:
      c2++;
      total++;
      break;

    case 3:
      c3++;
      total++;
      break;

    case 4:
      c4++;
      total++;
      break;

    case 5:
      b++;
      total++;
      break;

    case 6:
      n++;
      total++;
      break;
    }
  } while (voto < 7 && voto > 0);

  printf("Candidato 1: %.2f%%\n", (c1 / total) * 100);
  printf("Candidato 2: %.2f%%\n", (c2 / total) * 100);
  printf("Candidato 3: %.2f%%\n", (c3 / total) * 100);
  printf("Candidato 4: %.2f%%\n", (c4 / total) * 100);
  printf("Branco: %.2f%%\n", (b / total) * 100);
  printf("Nulo: %.2f%%\n", (n / total) * 100);

  vencedor(c1, c2, c3, c4, b, n);

  return 0;
}

void vencedor(int c1, int c2, int c3, int c4, int branco, int nulo) {
  if (c1 > c2 && c1 > c3 && c1 > c4 && c1 > branco && c1 > nulo) {
    printf("Candidato 1 Ganhou!");
  } else if (c2 > c1 && c2 > c3 && c2 > c4 && c2 > branco && c2 > nulo) {
    printf("Candidato 2 Ganhou!");
  } else if (c3 > c1 && c3 > c2 && c3 > c4 && c3 > branco && c3 > nulo) {
    printf("Candidato 3 Ganhou!");
  } else if (c4 > c1 && c4 > c2 && c4 > c3 && c4 > branco && c4 > nulo) {
    printf("Candidato 4 Ganhou!");
  } else if (branco > c1 && branco > c2 && branco > c3 && branco > c4 && branco > nulo) {
    printf("Branco Ganhou!");
  } else if (nulo > c1 && nulo > c2 && nulo > c3 && nulo > c4 && nulo > branco) {
    printf("Nulo Ganhou!");
  } else {
    printf("Empatou!");
  }
}