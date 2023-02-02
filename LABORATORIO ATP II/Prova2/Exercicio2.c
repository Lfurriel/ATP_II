#include <stdio.h>

int contaVogalMai(char *);
int contaVogalMin(char *);
int eVogalMai(char);
int eVogalMin(char);

int main(void) {

  char palavras[10000];
  int vogaisMai, vogaisMin;

  printf("Digite sua frase\n");
  scanf(" %[^\n]s", palavras);

  vogaisMai = contaVogalMai(palavras);
  vogaisMin = contaVogalMin(palavras);

  printf("Vogais maiusculas: %d\n", vogaisMai);
  printf("Vogais minusculas: %d\n", vogaisMin);

  return 0;
}

int contaVogalMai(char *palavra) {
  int count = 0;
  int i = 0;
  do {
    if (eVogalMai(palavra[i]))
      count++;
    i++;
  } while (palavra[i] != '\0');

  return count;
}

int contaVogalMin(char *palavra) {
  int count = 0;
  int i = 0;
  do {
    if (eVogalMin(palavra[i]))
      count++;
    i++;
  } while (palavra[i] != '\0');

  return count;
}

int eVogalMai(char letra) {
  if (letra == 'A' || letra == 'E' || letra == 'I' || letra == 'O' ||
      letra == 'U') {
    return 1;
  }
  return 0;
}

int eVogalMin(char letra) {
  if (letra == 'a' || letra == 'e' || letra == 'i' || letra == 'o' ||
      letra == 'u') {
    return 1;
  }
  return 0;
}
