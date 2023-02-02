/*Escreva um programa que leia um inteiro 3 < k < 10 e escreva 10^k números pares,
gerados aleatóriamente, no arquivo "pares.dat". Deve existir um espaço entre cada número*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main()
{
    int k, pot, i, par;
    FILE *fp = fopen("pares.dat", "w");

    srand(time(NULL));

    do {
        printf("Digite um número maior que 3 e menor que 10:\n");
        scanf("%d", &k);
    } while (k <= 3 || k >= 10);

    pot = pow(10, k);

    for (i = 0; i < pot; i++) {
        par = (rand() % 10000 / 2) * 2;
        fprintf(fp, "%d ", par);
    }

    fclose(fp);

    return 0;
}