#include <stdio.h>
#include <math.h>

//Prototipos de função
double distanciaMRU(double, double);
double velocidadeMRU(double, double);
double tempoMRU(double, double);
double distanciaMRUV(double, double, double);
double velocidadeFinalMRUV(double, double, double);
double velocidadeInicialMRUV(double, double, double);
double tempoTotalMRUV(double, double, double);

int main (void){
    int calculos, opcao, i;
    double tempo, velocidade, distancia, aceleracao;

    scanf("%d", &calculos);

    for(i = 0; i < calculos; i ++){

        scanf("%d", &opcao);        

        switch (opcao) {
            case 1: {
                 scanf("%lf", &velocidade);
                scanf("%lf", &tempo);
                printf("%.2lf\n", distanciaMRU(velocidade, tempo));
                break;
            }
               
            
            case 2: {
                scanf("%lf", &distancia);
                scanf("%lf", &tempo);
                printf("%.2lf\n", velocidadeMRU(distancia, tempo));
                break;
            }
                

            case 3: {
                scanf("%lf", &distancia);
                scanf("%lf", &velocidade);
                printf("%.2lf\n", tempoMRU(distancia, velocidade));
                break;
            }
                

            case 4: {
                scanf("%lf", &velocidade);
                scanf("%lf", &aceleracao);
                scanf("%lf", &distancia);
                printf("%.2lf\n", distanciaMRUV(velocidade, aceleracao, distancia));
                break;
            }
                

            case 5: {
                scanf("%lf", &velocidade);
                scanf("%lf", &aceleracao);
                scanf("%lf", &tempo);
                printf("%.2lf\n", velocidadeFinalMRUV(velocidade, aceleracao, tempo));
                break;
            }
                
            
            case 6: {
                scanf("%lf", &distancia);
                scanf("%lf", &aceleracao);
                scanf("%lf", &tempo);
                printf("%.2lf\n", velocidadeInicialMRUV(distancia, aceleracao, tempo));
                break;
            }
                

            case 7: {
                scanf("%lf", &distancia);
                scanf("%lf", &velocidade);
                scanf("%lf", &aceleracao);            
                printf("%.2lf\n", tempoTotalMRUV(distancia, velocidade, aceleracao));
                break; 
            } 
        }        
    }
    return 0;        
}

double distanciaMRU(double velocidade, double tempo) { // Case 1
    double resultado;
    resultado = velocidade*tempo;
    return (resultado);
}

double velocidadeMRU(double distancia, double tempo) { // Case 2
    double resultado;
    resultado = distancia/tempo;
    return (resultado);
}

double tempoMRU(double distancia, double velocidade) { // Case 3
    double resultado;
    resultado = distancia/velocidade;
    return (resultado);
}

double distanciaMRUV(double velocidade, double aceleracao, double tempo) { // Case 4
    double resultado;
    resultado = (velocidade*tempo)+(aceleracao*tempo*tempo)/2;
    return(resultado);
}

double velocidadeFinalMRUV(double velocidade, double aceleracao, double tempo) { // Case 5
    double resultado;
    resultado = velocidade + (aceleracao*tempo);
    return(resultado);
}

double velocidadeInicialMRUV(double distancia, double aceleracao, double tempo) { // Case 6
    double resultado;
    resultado = (distancia - (aceleracao*tempo*tempo)/2) / tempo;
    return(resultado);
}

double tempoTotalMRUV(double distancia, double velocidade, double aceleracao) { // Case 7
    double resultado;
    resultado = (sqrt((velocidade*velocidade) + (2*aceleracao*distancia)) - velocidade)/aceleracao;
    return (resultado); 
}
