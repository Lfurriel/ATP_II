#include <stdio.h>
#include <math.h>
#include <string.h>

int main() {

    typedef struct Planetas {
       char nome[21];
       double peso;
       double x, y, z;
    } Tplaneta;
    
    int n, m, i, j, op;
    double x1, y1, z1;
    double x2, y2, z2;
    double dist;
    char buscaPlaneta[21], buscaPlanetata[21];

    scanf("%d", &n);
    scanf("%d", &m);

    Tplaneta planetas[n];

    for(i = 0; i < n; i++){
        //printf("Le planeta %d\n", i);
        scanf(" %s", planetas[i].nome);
        scanf("%lf",&planetas[i].peso);
        scanf("%lf", &planetas[i].x);
        scanf("%lf", &planetas[i].y);
        scanf("%lf", &planetas[i].z);
    }

    for(j = 0; j < m; j ++){
        scanf("%d", &op);
        if(op == 1){ //distancia entre 2
            //printf("COMPARE\n");
            scanf(" %s", buscaPlaneta);
            //printf("COMPARE\n");
            scanf(" %s", buscaPlanetata);
            for(i = 0; i < n; i++){
                if(strcmp(buscaPlaneta, planetas[i].nome) == 0){
                    x1 = planetas[i].x;
                    y1 = planetas[i].y;
                    z1 = planetas[i].z;
                }
                if(strcmp(buscaPlanetata, planetas[i].nome) == 0){
                    x2 = planetas[i].x;
                    y2 = planetas[i].y;
                    z2 = planetas[i].z;
                }
            }
            dist = sqrt(pow((x2 - x1),2) + pow((y2 - y1),2) + pow((z2 - z1),2));
            printf("%.2lf\n", dist);
        }

        if(op == 2){ //coordenadas
            //printf("COORD\n");
            scanf(" %s", buscaPlaneta);
            for(i = 0; i < n; i++){
                if(strcmp(buscaPlaneta, planetas[i].nome) == 0){
                    printf("%.lf ", planetas[i].x);
                    printf("%.lf ", planetas[i].y);
                    printf("%.lf\n", planetas[i].z);
                }
            } 
        }

        if(op == 3){ //peso
            //printf("PESO\n");
            scanf(" %s", buscaPlaneta);
            for(i = 0; i < n; i++){
                if(strcmp(buscaPlaneta, planetas[i].nome) == 0){
                    printf("%.2lf\n", planetas[i].peso);
                }
            } 
        }
    }

    return 0;
}