#include <stdio.h>
#include <stdlib.h>

void crescente(double *, int);
void decrescente(double *, int, int);
void imprime(double *, int);

void main() {

    int N, k, i;
    double *vet;
    scanf("%d %d", &N, &k);

    vet = malloc(N * sizeof(double));

    for (i = 0; i < N; i++)
        scanf("%lf", &vet[i]);

    crescente(vet, k);
    decrescente(vet, k, N);
    imprime(vet, N);

}

void crescente(double *vet, int k) {

    int i, j;
    double aux;

   for (i = 1; i <= k; i++) {
        aux = vet[i];
        j = i - 1;

        while (aux < vet[j] && j >= 0) {
            vet[j + 1] = vet[j];
            j--;
        }

        vet[j+1] = aux;
    }
}

void decrescente(double *vet, int k, int N) {
    int i, j;
    double aux;

   for (i = k; i < N; i++) {
        aux = vet[i];
        j = i - 1;

        while (aux > vet[j] && j >= k) {
            vet[j + 1] = vet[j];
            j--;
        }

        vet[j+1] = aux;
    }

}

void imprime(double *vet, int N) {

    int i;

    for (i = 0; i < N; i++)
        printf("%.3lf ", vet[i]);

    printf("\n");
}