#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void shellSort(int);
void imprime(int);


char matriz[10000][60];

int main () {

    int N, i;
    scanf("%d", &N);
    
    for (i = 0; i < N; i ++)
        scanf(" %s", matriz[i]);

    shellSort(N);
    return 0;
}

void shellSort (int N) {

    int i, j, k, l;
    char str[60];
 
    k = (int)pow(2, (int)log2(N/4));
 
    while (k != 0) {
        for (l = 0; l < k; l ++) {
            for (i = l + k; i < N; i = i + k) {
                strcpy(str, matriz[i]);
                j = i;
                while (j - k >= 0 && strcmp(str, matriz[j-k]) < 0) {
                    strcpy(matriz[j], matriz[j-k]);
                    j = j - k;
                } 
                strcpy(matriz[j], str);
            }
        }

        imprime(N);
        k = k / 2;
    }
}

void imprime(int N) {
    int i = 0;
    for(;i < N; i++) {
      printf("%s ", matriz[i]);
    }
    printf("\n");
}