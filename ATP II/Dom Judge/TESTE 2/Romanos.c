#include <stdio.h>
#include <string.h>

int romanoParaDecimal(char *);
void decimalParaRomano(int);

int main(){
    int i, numeros, C, decimal, somando = 0;
    char leRomano[30];

    scanf("%d", &numeros);
    
    for(i = 0; i < numeros; i ++) {

        scanf("%d", &C);

        if(C == 1) {
            scanf("%s", leRomano);
            decimal = romanoParaDecimal(leRomano);
            somando += decimal;
            printf("%d\n", decimal);
        } else {
            scanf("%d", &decimal);
            decimalParaRomano(decimal);
        }

    }
  printf("%d\n", somando);
    return 0;
}

int romanoParaDecimal(char *romano) {

    int resultado = 0, len, i;
    int vetNum[30] = {0};

    len = strlen(romano);

    for(i = 0; i < len; i++) {

        if(romano[i] == 'I') {
            vetNum[i] = 1;
        } else if (romano[i] == 'V') {
            vetNum[i] = 5;
        } else if (romano[i] == 'X') {
            vetNum[i] = 10;
        } else if (romano[i] == 'L') {
            vetNum[i] = 50;
        } else if (romano[i] == 'C') {
            vetNum[i] = 100;
        } else if (romano[i] == 'D') {
            vetNum[i] = 500;
        } else if (romano[i] == 'M') {
            vetNum[i] = 1000;
        }
    }

    for(i = 0; i < len; i ++){
        if(vetNum[i+1] > vetNum[i]) {
            resultado += (vetNum[i+1] - vetNum[i]);
            i++;
        } else {
            resultado += (vetNum[i]);
        }
    }

    return resultado;
}

void decimalParaRomano(int decimal) {
    
  while(decimal > 0){
    
    if(decimal >= 1000) {
      printf("M");
      decimal -= 1000;
    } else if(decimal >= 900) {
      printf("CM");
      decimal -= 900;
    } else if(decimal >= 500) {
      printf("D");
      decimal -= 500;    
    } else if(decimal >= 400) {
      printf("CD");
      decimal -= 400;
    } else if(decimal >= 100) {
      printf("C");
      decimal -= 100;
    } else if(decimal >= 90) {
      printf("XC");
      decimal -= 90;
    } else if(decimal >= 50){
      printf("L");
      decimal -= 50;
    } else if(decimal >= 40) {
      printf("XL");
      decimal -= 40;
    } else if(decimal >= 10) {
      printf("X");
      decimal -= 10;
    } else if (decimal >= 9) {
      printf("IX");
      decimal -= 9;
    } else if (decimal >= 5) {
      printf("V");
      decimal -= 5;
    } else if (decimal >= 4) {
      printf("IV");
      decimal -= 4;      
    } else if (decimal >= 1) {
      printf("I");
      decimal -= 1;      
    }   
  }
  printf("\n");  
}
