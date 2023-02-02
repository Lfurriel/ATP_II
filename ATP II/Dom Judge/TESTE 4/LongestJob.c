#include <stdio.h>
#include <stdlib.h>

typedef struct elemento {
  int T;
  int C;
  struct elemento *prox;
} TElemento;

typedef struct {
  TElemento *inicio;
} TLista;

int tempo = 0;

FILE *fp, *fq, *fj;

void preencheLista(TLista *, int);
void iniciaLista(TLista *);
void inserir(TLista *, int, int);
void imprimir(TLista);
void longestJob(TLista, int);
void removeLista(TLista *, int, int);

int main() {

  int N;
  TLista lista;

  scanf("%d", &N);
  preencheLista(&lista, N);
  //imprimir(lista); //Imprime a lista completa (Usada para testes).
  longestJob(lista, N);

  return 0;
}

//Função responsável por receber as entradas e incluir nas listas
void preencheLista(TLista *lista, int N) {
  int T, C;

  lista->inicio = NULL; //Inicializa a lista

  for(; N > 0; N--) {
    scanf("%d %d", &T, &C);
    inserir(lista, T, C);
  }  

}

//Insere de forma ordenada
void inserir(TLista *lista, int T, int C) {

  TElemento *busca, *novo = malloc(sizeof(TElemento));

  novo->T = T;
  novo->C = C;

  if(lista->inicio == NULL) {
    novo->prox = NULL;
    lista->inicio = novo;
  }
  else if(novo->T < lista->inicio->T) {
    novo->prox = lista->inicio;
    lista->inicio = novo;
  }
  else {
    busca = lista->inicio;
    while(busca->prox && novo->T > busca->prox->T)
      busca = busca->prox;
    novo->prox = busca->prox;
    busca->prox = novo;
  } 
}

//Função responsável por imprimir os valores da lista
void imprimir(TLista lista) {

  TElemento *no = lista.inicio;

  printf("\nLISTA: ");

  while(no){
    printf("%d,%d ", no->T, no->C); //Ti,Ci Tj,Cj ... Exemplo: 7,20 7,45 
    no = no->prox;
  }
  printf("\n\n");
}

//Função responsavel por resolver o problema
void longestJob(TLista lista, int N) {

  TElemento *no;
  int tAux, cAux;

  for(; N > 0; N--) { //Laço de N execuções
    no = lista.inicio; //No aponta para o primeiro elemento da lista
    if(no->T > tempo) {
      /*Caso onde o T do primeiro elemento da lista irá ser executado só depois do tempo atual
      por exemplo no primeiro exemplo passado onde o primerio T = 7, nosso tempo começa em 0
      7 > 0 portanto o tempo passa a ser 7*/

      tempo = no->T; //No > tempo (variavel global que contabiliza o tempo de execução)
      tAux = no->T;
      cAux = no->C;
      while (no->prox != NULL && (tAux == no->prox->T && cAux < no->prox->C)) { 
        //Buscamos se tem algum T igual com um C menor que o nosso atual
        no = no->prox;
        tAux = no->T;
        cAux = no->C;      
      }
    } else {
      /*Caso onde possam ter 1 ou mais tarfas pendentes de execução, buscamos aquela onde o
      tempo é maior ou igual ao T e o maior C dentre todos*/
      tAux = no->T;
      cAux = no->C;
      while(no->prox != NULL) {
        /*O While percorre a lista toda em busca de encontrar o maior C de uma tarefa
        pendente de execução T <= tempo*/
        if(tempo >= no->prox->T && cAux < no->prox->C) {
          tAux = no->prox->T;
          cAux = no->prox->C;
        }
        no = no->prox;
      }
       
    }

    tempo += cAux; //Adicionamos o tempo que demora a execução(C) a variavel tempo global
  
    //printf("REMOVE: %d %d\n", tAux, cAux); //Usado para testes
    removeLista(&lista, tAux, cAux);
  }
}

//Função responsável por remover um nó da lista, buscamos aquela cujo T e C sejam iguais
void removeLista(TLista *lista, int T, int C) {
  TElemento *aux, *remover = NULL;

  if(lista->inicio->T == T && lista->inicio->C == C){
    remover = lista->inicio;
    lista->inicio = lista->inicio->prox;
  }
  else{
    aux = lista->inicio;
    while(aux->prox && (aux->prox->T <= T && aux->prox->C != C))
      aux = aux->prox;
    if(aux->prox){
      remover = aux->prox;
      aux->prox = aux->prox->prox;
    }
  }

  //printf("REMOVE: %d %d\n", remover->T, remover->C);
  printf("%d ", remover->C); //Printf resposta

  free(remover);
}