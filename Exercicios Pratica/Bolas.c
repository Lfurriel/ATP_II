//Prática de recursão

#include <stdio.h>

int bolas(int);

int main() {

    int pilhas;

    printf("Quantas pilhas?\n");
    scanf("%d", &pilhas);

    printf("\nResultam: %d bolas", bolas(pilhas));

    return 0;
}

int bolas(int n) {
    if(n == 1){
        return 1;
    } else {
        return(n*n + bolas(n-1));
    }
}
