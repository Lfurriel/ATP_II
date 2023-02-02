#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct biggo {
    int high;
    int low;
} BigInt;

#define max 200000

void quickSortBig(BigInt[max], int, int);
int testaMenorIgual(int, int, int, int);
int testaMaiorIgual(int, int, int, int);

int testaMenor(int, int, int, int);
void insertionSort(BigInt *, int);

void lerArquivo(BigInt*);
void escreverArquivoQ(BigInt*);
void escreverArquivoI(BigInt*);


int main() {

    BigInt vet[max];
    clock_t t;
    lerArquivo(vet);

    t = clock();
    quickSortBig(vet, 0, max-1);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("QuickSort demorou %.2f segundos", time_taken);
    escreverArquivoQ(vet);

    /*t = clock();
    insertionSort(vet, max);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("InsertionSort demorou %.2f segundos", time_taken); //O projeto pede que seja testado tbm com o Insertion Sort
    escreverArquivoI(vet);*/

    

    return 0;
}

void lerArquivo(BigInt *vet) {

    FILE *in = fopen("bigint.dat", "r");
    int i;

    if(in == NULL) {
        printf("Erro ao abrir");
        exit(0);
    }

    for(i = 0; i < max; i++) {
        fscanf(in, "%d%d", &vet[i].high, &vet[i].low);
    }

    fclose(in);
}

void escreverArquivoQ(BigInt *vet) {

    FILE *out = fopen("quick.dat", "w");
    int i;
    for(i = 0; i < max; i++) {
        fprintf(out, "%d %d\n", vet[i].high, vet[i].low);
    }

    fclose(out);
}

void quickSortBig(BigInt vet[max], int left, int right) {

    int i = left, j = right; 
    int tempH = vet[i].high, tempL = vet[i].low;

    if( left < right) {
        while(i < j) {
            while(testaMaiorIgual(vet[j].high, vet[j].low, tempH, tempL) && i < j)
                j--;
            vet[i].high = vet[j].high;
            vet[i].low = vet[j].low;

            while(testaMenorIgual(vet[i].high, vet[i].low, tempH, tempL) && i < j)
                i++;
            vet[j].high = vet[i].high;
            vet[j].low = vet[i].low;
        }

        vet[i].high = tempH;
        vet[i].low = tempL;

        quickSortBig(vet, left, i - 1);
        quickSortBig(vet, j + 1, right);
    }
}

int testaMaiorIgual(int high, int low, int tempHigh, int tempLow) {

    if((high > tempHigh) || (((high == tempHigh) && high < 0) && low <= tempLow)
    || (((high == tempHigh) && high >= 0) && low >= tempLow))
        return 1;

    return 0;

}

int testaMenorIgual(int high, int low, int tempHigh, int tempLow) {

    if((high < tempHigh) || (((high == tempHigh) && high < 0) && low >= tempLow)
    || (((high == tempHigh) && high >= 0) && low <= tempLow))
        return 1;

    return 0;

}

void insertionSort(BigInt *vet, int k) {

    int i, j;
    int auxL, auxH;

   for (i = 1; i <= k; i++) {
        auxH = vet[i].high;
        auxL = vet[i].low;
        j = i - 1;

        while (testaMenor(vet[j].high, vet[j].low, auxH, auxL) && j >= 0) {
            vet[j+1].high = vet[j].high;
            vet[j+1].low = vet[j].low;
            j--;
        }

        vet[j+1].high = auxH;
        vet[j+1].low = auxL;
    }
}

int testaMenor(int high, int low, int auxH, int auxL) {

    if((high > auxH) || (((high == auxH) && high < 0) && low < auxL)
    || (((high == auxH) && high >= 0) && low > auxL))
        return 1;

    return 0;

}

void escreverArquivoI(BigInt *vet) {

    FILE *out = fopen("insertion.dat", "w");
    int i;
    for(i = 0; i < max; i++) {
        fprintf(out, "%d %d\n", vet[i].high, vet[i].low);
    }

    fclose(out);
}