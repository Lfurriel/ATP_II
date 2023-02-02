/*Implementando todos os métodos sorts estudados, todas as ordenações 
estão sendo feitas em ordem crescente*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 15

void selectionSort(int*);
void bubbleSort(int*);
void insertionSort(int*);
void shellSort(int*);
void mergeSort(int*, int, int);
void merge(int*, int, int, int);
void quickSort(int*, int, int);
void quickSortAleardo(int*, int, int); //Quick sort ensinado pelo professor
void troca(int*, int*);

int main() {

    srand(time(NULL));
    int i, vet[MAX] = {8,	4,	2,	5,	7,	0,	0,	1,	2,	1,	3,	1,	2,	6,	8}; // 10, 9, 8, 7, 6};

    printf("Vetor não ordendado:\n");
    for(i = 0; i < MAX; i++) {
        //vet[i] = rand() % 10;
        printf("%d ", vet[i]);
    }
    printf("\n\n");

    //Descomentar qual método será utilizado:

    //selectionSort(vet);
    //bubbleSort(vet);
    //insertionSort(vet);
    //shellSort(vet);
    //mergeSort(vet, 0, MAX-1);
    //quickSort(vet, 0, MAX-1);
    //quickSortAleardo(vet, 0, MAX-1);


    printf("\n\nVetor ordendado:\n");
    for(i = 0; i < MAX; i++)
        printf("%d ", vet[i]);

    return 0;
}

void selectionSort(int *vet) {

    /*Em resumo o selection seleciona o menor elemento por uma busca sequencial, e posiciona esse
    elemento na posição válida*/

    int i, j, aux, index;

    for(i = 0; i < MAX; i++) {

        aux = vet[i];
        index = i;
        for(j = i+1; j < MAX; j++) { //Laço da busca sequencial para achar o menor elemento do vetor
            if(vet[j] < aux) {
                index = j;
                aux = vet[j];
            }
        }

        //Troca aux (menor elemento neste laço) com a "primeira" posição
        aux = vet[i]; 
        vet[i] = vet[index];
        vet[index] = aux;
    }
}

void bubbleSort(int *vet) {

    /*Em resumo o bubble sort compara se o próximo elemento é maior que o atual,
    se for, troca esses dois*/

    int i, j, aux;

    for(i = 1; i < MAX; i++) {
        for (j = 0; j <MAX-1; j++) { //Recomeça o laço
            if(vet[j] > vet[j+1]) { //Elemento em j é menor que o próximo
                //troca os elementos
                aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
            }
        }
    }

}

void insertionSort(int *vet) {

    /*Em resumo o insertion sort pega o elemento e vai voltando indice no vetor
    até encontrar a posição válida, nesse laço de volta ele vai passando o elemento
    para a próxima posição*/

    int i, j, aux;

    for(i = 1; i < MAX; i++) {
        aux = vet[i];
        j = i-1;
        while (aux < vet[j] && j>=0) {
            vet[j+1] = vet[j];
            j--;
        }
        
        vet[j+1] = aux;
    }

}

void shellSort(int *vet) {

    /*Em resumo o shell sort pega o vetor e divide em diferentes sub vetores. Esses sub vetores são
    passos dado na posição do vetor
    vet[i] -> vet[i+k] -> vet[i+2k] -> vet[i+3k]...
    o K é calculado e passa por um loop até 1
    
    A ideia de dividir é ordenar (pelo insertion sort) esse vetor em passos*/

    int i, j, k = 1, l, valor, furri;

    //while (k < (MAX/2))
        //k = 3*k+1;
    k = MAX/2;
    while(k != 1) {
        k = k/2;
        printf("PARA k = %d\n", k);
        for(l = 0; l < k; l++){
            for(i = l+k; i < MAX; i = i+k) {
                valor = vet[i];
                j = i;

                while (j-k >= 0 && vet[j-k] > valor) {
                    vet[j] = vet[j-k];
                    j = j-k;
                }

                vet[j] = valor;
                
            }
            for(furri = 0; furri < MAX; furri++)
                printf("%d ", vet[furri]);
            printf("\n\n");
        }

    }

}

void mergeSort(int *vet, int inicio, int fim) {

    /*O merge sort divide um vetor em diversos subvetores recursivamente, sempre dividindo eles pela
    metade após a divisão o 'merge' junta novamente os subvetores agora sim ordenando*/

    int meio;
    if (inicio < fim) {
        meio = inicio + (fim - inicio) / 2;

        mergeSort(vet, inicio, meio);
        mergeSort(vet, meio + 1, fim);

        merge(vet, inicio, meio, fim);
    }
}

void merge(int *vet, int inicio, int meio, int fim) {
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int L[n1], R[n2];
    printf("\n\nNOVO MERGE (%d %d %d):\n", inicio, meio, fim);
    for (i = 0; i < n1; i++) {
        L[i] = vet[inicio + i];
        //printf("\tL[%d]: %d --",i, L[i]);
    }
    //printf("\n");
    for (j = 0; j < n2; j++) {
        R[j] = vet[meio + 1 + j];
        //printf("\tR[%d]: %d --",j, R[j]);
    }

    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { //Aqui muda de crescente (<=) para decrescente (>=)
            vet[k] = L[i];
            i++;
        } else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }

    for(k = 0; k < MAX; k++)
        printf("%d ", vet[k]);
}

void quickSort(int *vet, int inicio, int fim) {

    int i = inicio;
    int j = fim; 
    int aux = vet[i];

    if( inicio < fim) {

        for(int k = 0; k < MAX; k++)
            printf("%d ", vet[k]);
        printf("\n\n");

        while(i < j) {
            while(vet[j] >= aux && i < j)
                j--;
            vet[i] = vet[j];
            while(vet[i] <= aux && i < j)
                i++;
            vet[j] = vet[i];
        }

        vet[i] = aux;

        quickSort(vet, inicio, i - 1);
        quickSort(vet, j + 1, fim);
    }
}

void quickSortAleardo(int *vet, int inicio, int fim) {

  int i, pivo, maior;

  if (inicio < fim) {//Enquanto ainda tiver mais de uma posição no vetor verificado
    
    pivo = inicio;

    troca(&vet[pivo], &vet[fim]);//Coloca o pivo no fim para facilitar as comparações
    maior = inicio;

    for (i = maior; i < fim; i++) {
      if (vet[i] < vet[fim]) {//Verifica o fim e se for igual verifica o inicio
        troca(&vet[i], &vet[maior]);//Chama a função troca, troca o maior com um elemento que seja menor que o pivo
        maior++;//Agora o meio elemeento para a comparação passa a ser o próximo do vetor
      }
    }

    troca(&vet[maior], &vet[fim]);//Quando sai do laço, coloca o pivo no seu devido lugar
    for(int k = 0; k < 10; k++)
            printf("%d ", vet[k]);
    printf("\n\n");
    quickSortAleardo(vet, inicio, maior - 1);//Chamada recursiva para a parte de baixo do vetor - ordena ela primeiro
    quickSortAleardo(vet, maior + 1, fim);//Chamada recursiva para a parte de cima do vetor
  }
}

void troca(int *valor1, int *valor2) {
  int aux;
  aux = *valor1;
  *valor1 = *valor2;
  *valor2 = aux;
}