#include <stdio.h>

void contaConsoante(char *, int *, int *);

int main(void) {

  char palavras[10000];
  int consoanteMai = 0, consoanteMin = 0;

  printf("Digite sua frase\n");
  scanf(" %[^\n]s", palavras);

  contaConsoante(palavras, &consoanteMai, &consoanteMin);

  printf("Consoantes maiusculas: %d\n", consoanteMai);
  printf("Consoantes minusculas: %d\n", consoanteMin);

  return 0;
}

void contaConsoante(char *frase, int *maiuscula, int *minuscula) {

  int count = 0;
  int i = 0;
  
  do {
    if (frase[i] == 'B' || frase[i] == 'C' || frase[i] == 'D' || frase[i] == 'F' || frase[i] == 'G' || frase[i] == 'H' ||
    frase[i] == 'J' || frase[i] == 'K' || frase[i] == 'L' || frase[i] == 'M' || frase[i] == 'N' || frase[i] == 'P' ||
    frase[i] == 'Q' || frase[i] == 'R' || frase[i] == 'S' || frase[i] == 'T' || frase[i] == 'V' || frase[i] == 'W' ||
    frase[i] == 'X' || frase[i] == 'Y' || frase[i] == 'Z')
        *maiuscula+=1;

    if (frase[i] == 'b' || frase[i] == 'c' || frase[i] == 'd' || frase[i] == 'f' || frase[i] == 'g' || frase[i] == 'h' ||
    frase[i] == 'j' || frase[i] == 'k' || frase[i] == 'l' || frase[i] == 'm' || frase[i] == 'n' || frase[i] == 'p' ||
    frase[i] == 'q' || frase[i] == 'r' || frase[i] == 's' || frase[i] == 't' || frase[i] == 'v' || frase[i] == 'w' ||
    frase[i] == 'x' || frase[i] == 'y' || frase[i] == 'z')
        *minuscula+=1;

    i++;
  } while (frase[i] != '\0');
}