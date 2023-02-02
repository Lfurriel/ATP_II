#include <stdio.h>
#include <math.h>
#include <string.h>

#define max 100000



int main(){

    char entrada[max];
    char delimitadores[max] = {0};
    char vetAbre[max];
    int fecha, abre;
    int valida = 1; //true
    int i, j, indice, count = 0, encontra;

    scanf(" %s", entrada);

    for(i = 0; i< strlen(entrada); i++){
        if(entrada[i] == '{' || entrada[i] == '}' || entrada[i] == '(' || entrada[i] == ')' || entrada[i] == '[' || entrada[i] == ']'){
            delimitadores[count] = entrada[i];
            count++;
        }
    }

    //printf("SAIU");

    for(i = 0; i < count; i++){
        if(delimitadores[i] == '}' || delimitadores[i] == ']' || delimitadores[i] == ')'){
            if (delimitadores[i] == '}'){
                //printf("Chegou %d", j);
                delimitadores[i] = 'A';
                encontra = 0;
                j = i-1;
               // printf("%d ", j);
                while (j>=0 && encontra == 0) {
                    //printf("A");
                   if(delimitadores[j] == 'A') {
                    j--;
                   } else if (delimitadores[j] == '{') {
                    delimitadores[j] = 'A';
                    encontra = 1;
                    break;
                   } else if (delimitadores[j] == '[' || delimitadores[j] == '('){
                    break;
                   }
                }
                if (encontra == 0){
                    //printf(" pinto %d\n", i);
                    valida = 0;
                    break; 
                }

            } else if (delimitadores[i] == ']') {
                delimitadores[i] = 'A';
                encontra = 0;
                j = i-1;
                while (j>=0 && encontra == 0) {
                   if(delimitadores[j] == 'A') {
                    j--;
                   } else if (delimitadores[j] == '[') {
                    delimitadores[j] = 'A';
                    encontra = 1;
                    break;
                   } else if (delimitadores[j] == '{' || delimitadores[j] == '('){
                    break;
                   }
                }
                if (encontra == 0){
                    //printf("%d\n", i);
                    valida = 0;
                    break; 
                }
              
            } else if (delimitadores[i] == ')') {
                delimitadores[i] = 'A';
                encontra = 0;
                j = i-1;
                while (j>=0 && encontra == 0) {
                   if(delimitadores[j] == 'A') {
                    j--;
                   } else if (delimitadores[j] == '(') {
                    delimitadores[j] = 'A';
                    encontra = 1;
                    break;
                   } else if (delimitadores[j] == '{' || delimitadores[j] == '['){
                    break;
                   } 
                }
                if (encontra == 0){
                    //printf("%d\n", i);
                    valida = 0;
                    break; 
                }
            }
        }
    }

    if(valida == 1){
        printf("S\n");
    } else {
        printf("N\n");
    }

    return 0;
}