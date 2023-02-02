#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));

  int max = 0, a, b, i, aux;
  FILE *txt = fopen("P3.txt", "w");

  max = 7; //+ rand() % 10000;
  fprintf(txt, "%d\n", max);

  a = 2 + rand() % 9;
  b = rand() % 2;
  fprintf(txt, "%d %d\n", a, b);
  aux = a;

  for (i = 1; i < max; i++) {
    a = 2 + rand() % 9;
    if ((i + 1) == aux)
      b = 0;
    else
      b = rand() % 2;
    fprintf(txt, "%d %d\n", a, b);
  }

  return 0;
}
