/* PROJETO 1 - MANIPULAÇÃO DE ARQUIVOS */

#include <stdio.h>
#include <string.h>

void copiaStr(char *, char *, char *);
void escreveLinhas(FILE*, FILE*, FILE*);

int main() {

    // Declaração dos arquivos
    FILE *fp = fopen("codigos.dat", "r");
    FILE *fq = fopen("palavras.dat", "r");
    FILE *fj = fopen("linhas.dat", "w");

    if (fp == NULL || fq == NULL) { // Validação da abertura dos arquivos
        printf("Erro ao abrir os arquivos!");
        return 0; // Encerra o programa caso não seja encontrado os arquivos
    }

    escreveLinhas(fp, fq, fj); // Chamada da função responsável por escrever o arquivo linhas.dat

    fclose(fp);
    fclose(fq);
    fclose(fj);
}

void escreveLinhas(FILE *codigos, FILE *palavras, FILE *linhas) { 

    // Declaração de variáveis auxiliares
    int i, j, leCodigo, aux = 0;
    //int contagemLinhas = 1;
    char lePalavra[200];
    char ultimasCinco[5][200];

    do {
        
        fscanf(codigos, "%d", &leCodigo);

        if (leCodigo == 0) { // Imprime uma linha apenas com 0
            fprintf(linhas, "0");
        } 
        
        else if (leCodigo > 0) { // Imprime as próximas "N" palavras do arquivo
            for (i = 0; i < leCodigo; i++) {
                fscanf(palavras, "%s", lePalavra);
                fprintf(linhas, "%s ", lePalavra);
                if (aux > 4) { // Validação caso já tenham passado 5 palavras, caso "true" chamamos a função copiaStr
                    copiaStr(&(ultimasCinco[0][0]), &(ultimasCinco[1][0]), &(lePalavra[0])); // Função para mudar o "vetor de string"
                }
                else {
                    strcpy(ultimasCinco[aux], lePalavra); // Adicionando no "vetor de string" para caso N < 0
                }
                aux++;
            }
        }

        else { // Imprime as N últimas palavras do arquivo
            for (leCodigo; leCodigo < 0; leCodigo++) {
                fprintf(linhas, "%s ", ultimasCinco[5 + leCodigo]);
            }
        }

        fprintf(linhas, "\n"); // Quebra de linha do arquivo
                            
    } while (!feof(codigos) && !feof(palavras)); // Enquanto não chegarmos no fim dos dois arquivos

    while (!feof(codigos)) { // Caso ainda sobre códigos, imprimindo os restantes
        fscanf(codigos, "%d", &leCodigo);
        fprintf(linhas, "%d ", leCodigo);
    }

    aux = 0;
    while (!feof(palavras)) { // Caso ainda sobre palavras, imprimindo as restantes (5 por linha), e contagem de linhas
        fscanf(palavras, "%s ", lePalavra); // O espaço depois de %s serve para não duplicar a última palavra caso o arquivo palavras termine com espaço
        fprintf(linhas, "%s ", lePalavra);
        aux++;
        if (aux % 5 == 0) { //Quebra de linhas a cada 5 palavras
            fprintf(linhas, "\n");
            // contagemLinhas++; //Não precisa contar as linhas
        }
    }

    // fprintf(linha, "\nLinhas: %d", contagemLinhas); // Não precisa imprimir a quantidade de linhas

}


void copiaStr(char *vetStr, char *vetStrMais, char *palavraNova) { 
    /* A função consiste em trocar a palavra da posição i pela palavra na posição
    i + 1 e por fim adicionar a nova palavra na posição 4 do vetor de string */

    int i;
    for (i = 0; i < 4; i++) {
        strcpy(vetStr, vetStrMais);
        vetStr += 200; // Passa para próxima palavra
        vetStrMais += 200;
    }
    strcpy(vetStr, palavraNova);
}