//Prática de recursão

#include <stdio.h>

void binario(int);

int main() {

    int decimal;

    printf("Digita:\n");
    scanf("%d", &decimal);

    binario(decimal);

    return 0;
}

void binario(int dec) {
    if (dec%2 == dec){
        printf("%d", dec);
    } else {
        binario(dec/2);
        printf("%d", dec%2);
    }
}