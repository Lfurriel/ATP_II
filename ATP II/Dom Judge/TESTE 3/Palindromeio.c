#include <stdio.h>
#include <string.h>

int palindromeio(char *, int);
int palindromo(char *, int, int);

int main() {
  char palavra[2001];
  int tamanho;

  scanf("%s", palavra);

  tamanho = strlen(palavra);
  //printf("%d", palindromo(palavra, 0, --tamanho));

  printf("%d", palindromeio(palavra, tamanho));

  return 0;
}

int palindromeio(char *pal, int tam) {

  char aux[tam];
  int i, j, k, count;
  int maior = 1, auxLen;

  for (i = 0; i < tam; i++) {
    for (j = (tam - 1); j > i; j--) {
      if (pal[i] == pal[j]) {
        count = 0;
        for (k = i; k < (j+1); k++) {
          aux[count] = pal[k];
          count++;
        }
        aux[count] = '\0';
        auxLen = strlen(aux);
        if (palindromo(aux, 0, --auxLen)) {
          auxLen++;
          if (auxLen > maior) {
            maior = auxLen;
          }
        }
      }
    }
  }

  return maior;
}

int palindromo(char *c, int i, int j) {

  if (j <= i) {
    //printf("Palindromo: %s\n", c);
    return 1;
  }

  if (c[i] == c[j]) {
    return palindromo(c, ++i, --j);
  } else {
    return 0;
  }

  return 0;
}