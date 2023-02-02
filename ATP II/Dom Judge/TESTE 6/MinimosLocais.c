#include <stdio.h>
#include <stdlib.h>

#define max 1000

int matriz[max][max];

void preencheMatriz(int);
//void imprime(N);
void minimosLocais(int, int);

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    preencheMatriz(N);
    //imprime(N);
    minimosLocais(N, M);

    return 0;
}

void preencheMatriz(int N) {
    int i, j;
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
}

void imprime(int N) {
    int i, j;
    printf("MATRIZ:\n\n");
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
}

void minimosLocais(int N, int M) {
    int alfa, beta, i, j , k, menor;
    for(i = 0; i < M; i++) {
        scanf("%d %d", &alfa, &beta);
        alfa--;
        beta--;
        
        menor = matriz[alfa][beta];
        for(j = alfa; j <= beta; j++) {
            for(k = alfa; k <= beta; k++) {
                if(matriz[j][k] < menor)
                    menor = matriz[j][k];
            }
        }
        printf("%d\n", menor);

    }
}
