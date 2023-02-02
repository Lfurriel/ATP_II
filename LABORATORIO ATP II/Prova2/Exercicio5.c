#include <stdio.h>

int maiusculas[26] = {0}, minusculas[26] = {0};

void contaRepetido(char *);


int main(void) {

  char palavras[10000] = {'\0'};
  int i;

  printf("Digite sua frase\n");
  scanf(" %[^\n]s", palavras);

  contaRepetido(palavras);

  for(i = 0; i < 26; i++) {
    if(maiusculas[i] > 1)
      printf("%c : %d\n", i+65, maiusculas[i]);

  }
    
  for(i = 0; i < 26; i++) {
    if(minusculas[i] > 1)
      printf("%c : %d\n", i+97, minusculas[i]);
  }
    

  return 0;
}

void contaRepetido(char *frase) {
  int i = 0;
  do {
    if(frase[i] >= 65 && frase[i] <= 90)
      maiusculas[frase[i] - 65]++;
    if(frase[i] >= 97 && frase[i] <= 122)
      minusculas[frase[i] - 97]++;
    i++;
  } while(frase[i] != '\0');
}