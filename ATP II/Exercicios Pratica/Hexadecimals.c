#include <stdio.h>
#include <locale.h>

int main(){
  FILE *hexadecimal = fopen("hexadecimal.txt", "w");
  FILE *decimal = fopen("decimals.txt", "r");
  int i = 0, j = 0, num[4], k;
  char hexa[8];
  if(decimal == NULL){
    printf("\nNão tem esse arquivo\n");
    return 0;
  }
  do{

    j = 0;
    fscanf(decimal, "%d", &num[i]);
    while(num[i] > 0){
    if(num[i] % 16 < 10){
      hexa[j] = (num[i] % 16) + 48; 
      } else if(num[i] % 16 == 10){
        hexa[j] = 'A';
      } else if(num[i] % 16 == 11){
        hexa[j] = 'B';
      } else if(num[i] % 16 == 12){
        hexa[j] = 'C';
      } else if(num[i] % 16 == 13){
        hexa[j] = 'D';
      } else if(num[i] % 16 == 14){
        hexa[j] = 'E';
      } else if(num[i] % 16 == 15){
        hexa[j] = 'F';
      }
      num[i] = num[i] / 16;
      j ++;
    }
    for(k = j - 1; k >= 0; k --){
    	fprintf(hexadecimal, "%c", hexa[k]);
}
      i++;
      fprintf(hexadecimal, "\n");
    }while(!feof(decimal));
    fclose(hexadecimal);
    fclose(decimal);
    return 0; 
}