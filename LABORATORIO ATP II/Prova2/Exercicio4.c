#include <stdio.h>

int contaPalavra(char *);

int main(void) {
  char palavras[10000];
  int quantidade = 0;

  printf("Digite sua frase\n");
  scanf(" %[^\n]s", palavras);

  quantidade = contaPalavra(palavras);

  printf("Palavras: %d", quantidade);

  return 0;
}

int contaPalavra(char *frase) {
  int count = 1;

  int i = 0;
  do {
    if (frase[i] == ' ')
      count++;
    i++;
  } while (frase[i] != '\0');

  do {
    if (frase[i] == ' ')
      count--;
    i--;
  } while (frase[i] == ' ');
  return count;
}