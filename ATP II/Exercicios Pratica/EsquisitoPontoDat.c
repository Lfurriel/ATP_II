/*Escreva um programa que leia o arquivo "pares.dat" e troque os espaços em
branco por letras maiúsculas em ordem sequencial no arquivo "esquisto.dat"

Use o programa ParesPontoDat.c para gerar o arquivo*/

#include <stdio.h>

int main() {

    char alfa[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    int valor, i = 0;
    FILE *par, *esquisito;

    par = fopen("pares.dat", "r");
    esquisito = fopen("esquisito.dat", "w");

    if (par == NULL) {
        printf("Arquivo pares.dat não existe!\n");
        return 0;
    }

    do {
        fscanf(par, "%d", &valor);
        fprintf(esquisito, "%d%c", valor, alfa[i % 26]);
        i++;
    } while (!feof(par));

    fclose(par);
    fclose(esquisito);

    return 0;
}