#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
  srand(time(NULL));

  int max = 0, a, b, c, i;
  FILE *txt = fopen("P4.txt", "w");

  max = rand() % 1000;
  b = 1 + rand() % 9;
  fprintf(txt, "%d %d\n", max, b);

  for (i = 0; i < max; i++) {
    a = i+1;
    b = rand() % max;
    c = 1 + rand() % 199;
    
    fprintf(txt, "%d %d %d\n", a, b, c);
  }

  return 0;
}