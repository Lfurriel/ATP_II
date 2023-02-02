#include <stdio.h>
#include <stdlib.h>

//Declaracao das structs de lista e elemento da lista
typedef struct elemento {
  int idade; //idade do individuo
  int instante; //instante de chegada
  struct elemento *prox;
} TFila;

void preenche(TFila **);
void ordena(TFila **, int, int);
void atendimento(TFila **);
void insereFila(TFila **, TFila *);
void remover(TFila **);
void imprime(TFila *, int);

int main() {

    TFila *fila = NULL;

    preenche(&fila);
    atendimento(&fila);

    return 0;
}

void preenche(TFila **fila) {

    int I, T, N;
    scanf("%d", &N);

    for(; N > 0; N--){
        scanf("%d %d", &I, &T);
        ordena(fila, I, T);
    }

}

void ordena(TFila **fila, int I, int T) {

    TFila *busca, *antes, *novo = malloc(sizeof(TFila));
    int flag;

    novo->idade = I;
    novo->instante = T;

    if(!(*fila)) {
        *fila = novo;
        novo->prox = NULL;
    } else if(novo->instante < (*fila)->instante ||
    (novo->instante == (*fila)->instante && novo->idade > 59 && novo->idade > (*fila)->idade)) {
        novo->prox = (*fila);
       (*fila) = novo;        
    } else {
        if(novo->idade >59) {
            antes = busca = (*fila);
            flag = 1;           
            while (busca && novo->instante >= busca->instante && flag) {
                if (novo->instante == busca->instante && novo->idade > busca->idade)
                    flag = 0;
                if(flag) {
                    antes = busca;
                    busca = busca->prox;  
                }
            }
        } else {
            antes = busca = (*fila);
            while (busca && novo->instante >= busca->instante) {
                antes = busca;
                busca = busca->prox;
            }
        }
        antes->prox = novo;
        novo->prox = busca;
    }
}

void atendimento(TFila **fila) {

    TFila *aux, *outraFila = NULL;
    int tempo = 3, idade, flag = 1, instante;

    instante = (*fila)->instante;
    idade = (*fila)->idade;

    insereFila(&outraFila, *fila);
    remover(fila);

    while ((*fila) || outraFila) {
        if(tempo >= 3) {
            tempo = 0;
            if(!outraFila) {
                insereFila(&outraFila, *fila);
                instante = (*fila)->instante;
                remover(fila);
                flag = 1;
            }
            idade = outraFila->idade;
            remover(&outraFila);
        }

        while ((*fila) && instante >= (*fila)->instante) {
            insereFila(&outraFila, *fila);
            remover(fila);
            flag = 1;
        }

        if(flag)
            imprime(outraFila, idade);
        
        tempo++;
        instante++;
        flag = 0;
        
    }
    
}

void insereFila(TFila **outra, TFila *elem) {

    TFila *busca, *antes;
    TFila *novo;
    novo = malloc(sizeof(TFila));

    novo->idade = elem->idade;
    novo->instante = elem->instante;

    if (!(*outra)) {
        (*outra) = novo;
        novo->prox = NULL;
        return;
    } else if (novo->idade > 59) {
        if (novo->idade > (*outra)->idade) {
            novo->prox = *outra;
            *outra = novo;
            return;
        }
        
        busca = (*outra)->prox;
        antes = *outra;

        while (busca) {
            if(novo->idade > busca->idade){
                antes->prox = novo;
                novo->prox = busca;
                return;
            }
            antes = busca;
            busca = busca->prox;
        }
    }

    busca = (*outra)->prox;
    antes = (*outra);
    while (busca) {   
        antes = busca;    
        busca = busca->prox;
    }

    antes->prox = novo;
    novo->prox = NULL;
    
}

void remover(TFila **fila) {
    TFila *removido;

    if (!(*fila))
        return;
    
    removido = (*fila);
    (*fila) = (*fila)->prox;

    free(removido);
}

void imprime(TFila *fila, int idade) {

    printf("%d ", idade);

    while(fila) {
        printf("%d ", fila->idade);
        fila = fila->prox;
    }
    printf("\n");
}