//Solução da prova

#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
    int num;
    struct lista *prox, *prev;
} TLista;

void insereLista(TLista **head, TLista **tail, int N) {

    TLista *novo = malloc(sizeof(TLista)), *busca;
    novo->num = N;
    novo->prox = NULL;

    if(N > ((*head)->num + (*tail)->num)/2) { // Mais próximo do tail
        busca = (*tail);
        while (busca && busca->num > N)
            busca = busca->prev;
        
        if(busca == (*tail)) {
            (*tail)->prox = novo;
            novo->prev = (*tail);
            (*tail) = novo;
        } else {
            novo->prev = busca;
            novo->prox = busca->prox;
            busca->prox = novo;
            novo->prox->prev = novo;
        }
    } else { //Busca da head
        busca = (*head);
        while (busca && busca->num < N)
            busca = busca->prox;
        if(busca == (*head)) {
            novo->prox = (*head);
            (*head)->prev = novo;
            (*head) = novo;
        } else {
            novo->prox = busca;
            novo->prev = busca->prev;
            busca->prev->prox = novo;
            busca->prev = novo;
        }
        
    }

}

TLista* buscaLista(TLista *head, TLista *tail, int N) {
    
    TLista *busca;

    if(!head)
        return NULL;
    if(head == tail && head->num == N)
        return head;
    else if(head == tail && head->num != N)
        return NULL;

    if(N > (head->num + tail->num)/2) {
        busca = tail;
        while (busca && busca->num > N)
            busca = busca->prev;
        
    } else {
        busca = head;
        while (busca && busca->num < N)
            busca = busca->prox;
        
    }

    return busca;
}
