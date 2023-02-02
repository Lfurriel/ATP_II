#include <stdio.h>

int count = 0, limite;
int torre1, torre2 = 0, torre3 = 0;


void mover(int d, char origem, char destino, char aux){
    //printf("%d\n", d);
    if(d==1){
        //printf("de %c para %c\n", origem, destino);
        if(origem == 'A' && destino == 'B'){
            torre1--;
            torre2++;
        } else if (origem == 'A' && destino == 'C'){
            torre1--;
            torre3++;
        } else if (origem == 'B' && destino == 'C'){
            torre2--;
            torre3++;
        } else if (origem == 'B' && destino == 'A'){
            torre2--;
            torre1++;
        } else if (origem == 'C' && destino == 'A'){
            torre3--;
            torre1++;
        } else if (origem == 'C' && destino == 'B'){
            torre3--;
            torre2++;
        }
        //printf("Torres: [%d] [%d] [%d]\n", torre1, torre2, torre3);
        count++;
        if(count == limite){
            printf("%d %d %d\n", torre1, torre2, torre3);
        }
    } else {
        mover(d-1, origem, aux, destino);
        mover(1, origem, destino, aux); 
        mover(d-1, aux, destino, origem);
    }
}

int main(){

    int discos;
    scanf("%d", &discos);
    scanf("%d", &limite);
    torre1 = discos;

    //printf("Torres: [%d] [%d] [%d]\n", torre1, torre2, torre3);
    mover(discos, 'A', 'C', 'B');
   // printf("\n\n%d Movimentos", count);

    return 0;
}