#include <stdio.h>
#include <stdlib.h>

int count = 0, limite, discos;
int torreA, torreB = 0, torreC = 0; //Contagem de pinos em cada torre - índice vetor
int vetTorreA[20], vetTorreB[20], vetTorreC[20]; //Vetores que guardarao quais discos estao em cada torre
int pinosA, pinosB, pinosC;

void hanois (int, char, char, char);
void muda (char, char);
void imprime();

int main(){

    int i;
    scanf("%d", &discos);
    scanf("%d", &limite);

    for (i = 0; i< discos; i++) {
        vetTorreA[i] = 1;
        vetTorreB[i] = vetTorreC[i] = 0;
    }

    torreA = discos;
    if(limite > 0 && discos > 0){
        hanois(discos, 'A', 'C', 'B');
    } else if (limite == 0 && discos > 0) {
      imprime();
    } else {
      printf("0\n0\n0");
    }
    

    return 0;
}

void hanois(int d, char origem, char destino, char aux){
    //printf("%d\n", d);
    if(d==1){
        muda(origem, destino);
    } else {
        hanois(d-1, origem, aux, destino);
        hanois(1, origem, destino, aux); 
        hanois(d-1, aux, destino, origem);
    }
}

void muda(char origem, char destino) {
    int *discO, *discD, i;

    //printf("de %c para %c\n", origem, destino);

    if(origem == 'A' && destino == 'B') {
        torreA--;
        torreB++;
        discO = vetTorreA;
        discD = vetTorreB;
    } else if (origem == 'A' && destino == 'C') {
        torreA--;
        torreC++;
        discO = vetTorreA;
        discD = vetTorreC;
    } else if (origem == 'B' && destino == 'C') {
        torreB--;
        torreC++;
        discO = vetTorreB;
        discD = vetTorreC;
    } else if (origem == 'B' && destino == 'A') {
        torreB--;
        torreA++;
        discO = vetTorreB;
        discD = vetTorreA;
    } else if (origem == 'C' && destino == 'A') {
        torreC--;
        torreA++;
        discO = vetTorreC;
        discD = vetTorreA;
    } else if (origem == 'C' && destino == 'B') {
        torreC--;
        torreB++;
        discO = vetTorreC;
        discD = vetTorreB;
    }

    i = 0;

    while (discO[i] == 0) {
        i++;
    }

    discO[i] = 0;
    discD[i] = 1;
    
    //printf("Torres: [%d] [%d] [%d]\n", torreA, torreB, torreC);
    count++;
    if(count == limite){
        imprime();
        //printf("%d %d %d\n", torreA, torreB, torreC);
    }
}

void imprime() {

    int i, fim;

    fim = 0;
    for(i = 0; i < discos; i++){
        if(vetTorreA[i] == 1){
            printf("%d ", i + 1);
            fim = 1;
        } else if (i == discos-1 && vetTorreA[i] == 0 && !fim){
            printf("0");
        }
    }
    printf("\n");

    fim = 0;
    for(i = 0; i < discos; i++){
        if(vetTorreB[i] == 1){
            printf("%d ", i + 1);
            fim = 1;
        } else if (i == discos-1 && vetTorreB[i] == 0 && !fim){
            printf("0");
        }
    }
    printf("\n");

    fim = 0;
    for(i = 0; i < discos; i++){
        if(vetTorreC[i] == 1){
            printf("%d ", i + 1);
            fim = 1;
        } else if (i == discos-1 && vetTorreC[i] == 0 && !fim){
            printf("0");
        }
    }
}