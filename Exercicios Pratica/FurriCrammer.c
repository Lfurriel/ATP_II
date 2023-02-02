//Aplicando regra de Crammer para praticar uso de fuunções em C

#include <stdio.h>
#include <locale.h>

int tamanho; //tamanho do sistema

//Protótipos das funções
void leitura(double *, double *); // (Matriz, vetor de resultado da equação)
double calculaDeterminante(double[3][3]); // (Matriz)
double mudaMatriz(double[3][3], double[3], int); // (Matriz, vetor de resultado da equação, coluna a ser trocada)

int main () {
    int i, j;
    double matriz[3][3], vetResultadoEq[3], determinante, determinanteVariavel[3];
    leitura(&(matriz[0][0]), &(vetResultadoEq[0]));
    printf("\n\nMatriz Original:\n");
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            printf("%.lf\t", matriz[i][j]);        
        }
        printf("\n");   
    }
    determinante = calculaDeterminante(&(matriz[0][0]));
    if(determinante == 0){
        printf("Determinante = 0 - Não é possível calcular, SI\n");
        return 0;
    } else {
        for (i=0; i < tamanho; i++) { 
            determinanteVariavel[i] = mudaMatriz (matriz, vetResultadoEq, i);
        }
    }

    printf("\n\nResultados:\n");
    printf("Determinante: %.2lf\n", determinante);
    printf("X: %.2lf\n", determinanteVariavel[0]/determinante);
    printf("Y: %.2lf\n", determinanteVariavel[1]/determinante);
    if(tamanho == 3){
        printf("Z: %.2lf\n", determinanteVariavel[2]/determinante);
    }
    
   
    return 0;
}

void leitura(double *matriz, double *resultado){
    int i, j;
    float *maux= matriz; //sei o que é isso não
    do {
        printf("Qual o tamanho do sistema? ");
        scanf("%d", &tamanho);
        if(tamanho < 2 || tamanho > 3){
            printf("Tamanho precisa ser 2 ou 3\n");
        }
    } while(tamanho < 2 || tamanho > 3);
    for(i = 1; i <= tamanho; i++){
        printf("Insira os coeficientes da %dª equação: ", i);
        for(j = 0; j < tamanho; j ++){
            scanf("%lf", &(*matriz));
            matriz++;
        }
        printf("Insira o resultado da %dª equação: ", i);
        scanf("%lf", &(*resultado));
        resultado++;
    }
}

double calculaDeterminante(double matriz[3][3]) {
    double det;
    if(tamanho == 2) {
        det = ((matriz[0][0]*matriz[1][1]) - (matriz[0][1]*matriz[1][0]));
    } else {
       det =((matriz[0][0]*matriz[1][1]*matriz[2][2]) + (matriz[0][1]*matriz[1][2]*matriz[2][0]) +
            (matriz[0][2]*matriz[1][0]*matriz[2][1]) - (matriz[0][0]*matriz[1][2]*matriz[2][1]) -
            (matriz[0][1]*matriz[1][0]*matriz[2][2]) - (matriz[0][2]*matriz[1][1]*matriz[2][0]));
    }
    return det;
}

double mudaMatriz(double matriz[3][3], double resultado[3], int coluna) {
    int i,j;
    double matrizAlt[3][3];
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            matrizAlt[i][j] = matriz[i][j];        
        }   
    }
    printf("\n\n\n");
    for (i = 0; i < tamanho; i++) {
        matrizAlt[i][coluna] = resultado[i]; 
    }
    for (i = 0; i < tamanho; i++) {
        for (j = 0; j < tamanho; j++) {
            printf("%.lf\t", matrizAlt[i][j]);        
        }
        printf("\n");   
    }     
    return(calculaDeterminante(matrizAlt));
}