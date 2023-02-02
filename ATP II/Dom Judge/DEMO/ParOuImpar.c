#include <stdio.h>

int main(){

    int n; //numero de jogadas
    int a, b, i;
    //printf("Digite o número de jogadas: ");

    scanf("%d", &n);    
        
    for(i = 1; i <= n; i++) {

        scanf("%d", &a);
        scanf("%d", &b);

        //printf("%d + %d = %d\t",a,b,a+b);
        
        if((a+b) % 2 == 0) {
            printf("A\n");
        } else {
            printf("B\n");
        }

    } 

    return 0;

}