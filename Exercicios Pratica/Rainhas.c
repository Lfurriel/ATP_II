/*Posiciona N rainhas em um tabuleiro N*N de forma que nenhuma rainha consiga eliminar outra*/

#include <stdio.h>

int max, tabuleiro[40][40] = {0};
int vetColuna[40] = {0};
int diagonalDireita[79] = {0};
int diagonalEsquerda[79] = {0};

int linhas (int);
int testaRainha (int, int);

int main () {

    printf("Quantas rainhas?\n");
    scanf("%d", &max);

    if (linhas(0)) {
        printf("Deu certo!\n\n");
        for(int i = 0; i < max; i++){
            for(int j = 0; j < max; j++){
                printf("[%d] ", tabuleiro[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("\n\nERRO!\n\n");
        exit(0);
    }

    return 0;
}

int linhas (int n) {
    int i;

    for(i = 0; i < max; i++) {
        tabuleiro[n][i] = 1;

        if(n == max-1 && testaRainha(n, i)) {
            vetColuna[i] = 1;
            diagonalDireita[n+i] = 1;
            diagonalEsquerda[(n-i)+(max-1)] = 1;
            return 1;
        } else if (n < max-1 && testaRainha(n, i) && linhas(n+1)) {
            vetColuna[i] = 1;
            diagonalDireita[n+i] = 1;
            diagonalEsquerda[(n-i)+(max-1)] = 1;
            return 1;
        }

        tabuleiro[n][i] = 0;
        vetColuna[i] = 0;
        diagonalDireita[n+i] = 0;
        diagonalEsquerda[(n-i)+(max-1)] = 0;
        
    }
    return 0;
}

int testaRainha(int linha, int coluna) {
    int auxL, auxC;
    //printf("%d %d\n", coluna, linha);

    //Testa coluna
    auxL = linha - 1;
    for(; auxL >= 0; auxL--) {
        if(tabuleiro[auxL][coluna] == 1) {
            //printf("Alo?");
            return 0; //Encontrou rainha
        }
    }

    //Testa diagonal direita
    auxL = linha - 1;
    auxC = coluna + 1;
    for(; auxC < max; auxC++) {
        if(tabuleiro[auxL][auxC] == 1) {
            return 0; //Encontrou rainha
        }
        auxL--;
    }

    //Testa diagonal esquerda
    auxL = linha - 1;
    auxC = coluna - 1;
    for(; auxC >= 0; auxC--) {
        if(tabuleiro[auxL][auxC] == 1) {
            return 0; //Encontrou rainha
        }
        auxL--;
    }

    return 1;
    
}
