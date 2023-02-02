#include <stdio.h>
#include <stdlib.h>

int binarySearchAsc(int *, int, int, int);
int binarySearchDesc(int *, int, int, int);
void imprime(int *, int);

int main () {

    int N, M, i, *vet, *busca;
    int aux;
    scanf("%d", &N);

    vet = malloc(N * sizeof(int));

    for(i = 0; i < N; i++)
        scanf("%d", &vet[i]);

    scanf("%d", &M);
    busca = malloc(M * sizeof(int));
    for(i = 0; i < M; i++)
        scanf("%d", &busca[i]);
    
    for(i = 0; i < M; i++) {
        aux = binarySearchAsc(vet, 0, N/2-1, busca[i]);
        if(aux == -1)
            aux = binarySearchDesc(vet, N/2, N-1, busca[i]);
        printf("%d ", aux);
    }    
        
    return 0;
}


void imprime(int*vet, int N) {
    int i = 0;
    printf("IMPRIME VETOR:\n");
    for(; i < N; i++)
        printf("%d ", vet[i]);
    printf("\n\n");

}

int binarySearchAsc(int *arr, int l, int r, int x) {
    if (r >= l) {

        int mid = l + (r - l) / 2;
 
        if (arr[mid] == x)
            return mid;
 
        if (arr[mid] > x)
            return binarySearchAsc(arr, l, mid - 1, x);
 
        return binarySearchAsc(arr, mid + 1, r, x);
    }

    return -1;
}

int binarySearchDesc(int *arr, int l, int r, int x) {
    if (r >= l) {

        int mid = l + (r - l) / 2;
 
        if (arr[mid] == x)
            return mid;
 
        if (arr[mid] < x)
            return binarySearchDesc(arr, l, mid - 1, x);
 
        return binarySearchDesc(arr, mid + 1, r, x);
    }

    return -1;
}

