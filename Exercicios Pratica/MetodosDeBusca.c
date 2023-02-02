#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprime(int *, int);
int buscaSequencial(int, int, int *);
int buscaBinaria(int *, int, int);

int main() {

    int *vet, max, i, busca;

    scanf("%d", &max);
    vet = malloc(max * sizeof(int));

    for(i = 0; i < max; i++) {
        vet[i] = i;//1 + rand() % max;
    }

    imprime(vet, max);

    scanf(" %d", &busca);

    printf("\nBusca sequencial - indice: %d\n",buscaSequencial(busca, max, vet));
    printf("Busca Binaria - indice: %d\n", buscaBinaria(vet, max, busca));

    return 0;
}

void imprime(int *vet, int max) {

    int i;
    
    for(i = 0; i < max; i++)
        printf("%d ", vet[i]);

}

int buscaSequencial(int n, int max, int *vet) {
    int i = 0, flag = 1, retorno = -1;

    while (i < max && flag) {
        if(vet[i] == n) {
            retorno = i;
            flag = 0;
    
        }
        i++;
    }

    return retorno;
    
}

int buscaBinaria(int *vet, int N, int val) {

    int min = 0, max = N, meio;

    if(vet[min] == val)
        return min;
    if(vet[max] == val)
        return max;
    meio = (min+max)/2;
    while(vet[meio] != val && min < max) {
        if(val > vet[meio])
            min = meio;
        else
            max = meio;
        meio = (min+max)/2;
    }

    if(vet[meio] == val)
        return meio;
    else return -1;

    
}
