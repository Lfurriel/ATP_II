#include <stdio.h>
#include <stdlib.h>

//Declaracao das structs de lista e elemento da lista
typedef struct Elemento {
  int id;
  int K;
  int O;
  struct Elemento *prox;
} TElemento;

typedef struct lista {
  TElemento *inicio;
  TElemento *fim;
  int quantidade;
} TLista;

// Prototipos de funcao
void preencheLista(TLista *, int);
void iniciaLista(TLista *);
void insereInicio(TLista *, int, int, int);
void insereNovo(TLista *, int, int, int);
void imprimirCompleta(TLista);
void josephus(TLista *);
void removeElemento(TLista *, int);
void reinsere(TLista *);

int ultimoMorto[2]; //[0] = id, [1] = K

int main() {

  int N; // Numero de pessoas
  TLista lista;
  scanf("%d", &N); // Ler numero de pessoas na lista
  preencheLista(&lista, N);
  //imprimirCompleta(lista); //Usado para testes
  if(N > 1)
    josephus(&lista);

  printf("%d", lista.inicio->id);

  return 0;
}


// Funcao responsavel por preencher a lista com as variaveis de entrada
void preencheLista(TLista *lista, int N) {
  int i, K, O;

  iniciaLista(lista);

  scanf("%d %d", &K, &O);
  insereInicio(lista, 1, K, O); // Primeiro valor a ser preenchido, caso especial

  for (i = 2; i <= N; i++) {
    scanf("%d %d", &K, &O);
    insereNovo(lista, i, K, O);
  }
}

// Funcao responsavel por inicializar a lista circular
void iniciaLista(TLista *lista) {
  ultimoMorto[0] = ultimoMorto[1] = 0; //Limpamos o valores do ultimo elemento morto para validação

  lista->inicio = NULL;
  lista->fim = NULL;
  lista->quantidade = 0;
  //Inicialização das variaveis da struct TLista
}

// Funcao responsavel por inserir o primeiro valor da lista circular
void insereInicio(TLista *lista, int id, int K, int O) {

  /*Insercao no inicio de uma lista circular e um caso especial
  uma vez que precisamos mover o ponteiro lista->inicio e o
  ponteiro lista->fim*/
    
  TElemento *novo = malloc(sizeof(TElemento));

  novo->id = id;
  novo->K = K;
  novo->O = O;
  
  novo->prox = lista->inicio;
  lista->inicio = novo;
  if(lista->fim == NULL)
    lista->fim = novo;
  lista->fim->prox = lista->inicio;
  lista->quantidade++;
}

// Funcao responsavel por inserir um valor na lista circular
void insereNovo(TLista *lista, int i, int K, int O) {

  /*A funcao insere o elemento no ultimo no da lista, portanto nao
  e uma insercao ordenada*/

  TElemento *novo = malloc(sizeof(TElemento));

  novo->id = i;
  novo->K = K;
  novo->O = O;
  lista->fim->prox = novo; //Antigo ultimo elemento aponta para o novo fim
  lista->fim = novo; //Ponteiro de fim da lista aponta para o novo elemento
  novo->prox = lista->inicio; //Novo elemento aponta para o inicio da lista

  lista->quantidade++;
}

// Funcao responsavel por imprimir a TODA a lista circular
void imprimirCompleta(TLista lista) {

  /*Função usada mais para debug e quando estava fazendo
  testes de mesa*/

  TElemento *elemento = lista.inicio;

  printf("\n\n***** IMPRIMINDO LISTA *****\n");
  printf("\nQuantidade: %d\n", lista.quantidade);
  do {
    
    printf("%d ", elemento->id);
    printf("%d ", elemento->K);
    printf("%d\n", elemento->O);

    elemento = elemento->prox;
  } while (elemento != lista.inicio);
  printf("\n");
}

//Funcao responsavel por resolver o problema de Josephus
void josephus(TLista *lista) {
  int passos, auxId, auxK, auxO;
  TElemento *aux, *elemento = lista->inicio;
  passos = elemento->K;
  do {
    while (passos != 0) {
      passos--;
      if(passos)
        elemento = elemento->prox; // Andamos até o próximo elemento
    }

    //printf("Morre: %d\n", elemento->id); // Usado para testes
    
    
    auxId = elemento->id;
    auxK = elemento->K;
    auxO = elemento->O;
    //Salvamos os campos em variaveis auxiliares antes de removermos da lista

    passos = elemento->K; //Atualizamos os passos a serem dados
    
    removeElemento(lista, elemento->id); //Chamamos funcao de remover elemento da lista

    if(auxO) { //Validamos se opercao == 1
      //printf("Revive: %d\n",ultimoMorto[0]); // Usado para testes
      reinsere(lista);
    }
    //printf("\n");
    
    ultimoMorto[0] = auxId;
    ultimoMorto[1] = auxK;  
    
    elemento = lista->inicio; // voltamos o elemento para o inicio da lista

    if(auxId < lista->fim->id) { // Casos onde o id nao e o ultimo elemento da lista
      while (auxId > elemento->id && elemento->prox != lista->inicio)
      elemento = elemento->prox; //Buscamos o elemento seguinte daquele que acabamos de "matar"
    }

  } while (lista->quantidade > 1);
  // Repetimos a função enquanto existem mais de um elemento "vivo" na lista
}

// Funcao responsavel por remover um elemento da lista
void removeElemento(TLista *lista, int id) {

  TElemento *aux, *removido = NULL;

    
  if(lista->inicio->id == id) {
    //Caso onde o elemento a ser removido e o primeiro da lista
    removido = lista->inicio;
    lista->inicio = lista->inicio->prox; // Inicio da lista aponta para o prox elemento
    lista->fim->prox = lista->inicio; //Fim da lista aponta para o novo inicio
    lista->quantidade--;
  } else {
    //Caso onde iremos procurar o elemento no meio da lista circular
    aux = lista->inicio;
    while(aux->prox != lista->inicio && aux->prox->id != id)
      aux = aux->prox;
    if(aux->prox->id == id){
      if(lista->fim == aux->prox) {
        /*Elemento a ser removido esta no fim da lista.
        Caso particular pois devemos mover o ponteiro fim da lista*/
        removido = aux->prox;
        aux->prox = removido->prox;
        lista->fim = aux;
      } else {
        removido = aux->prox;
        aux->prox = removido->prox;
      }
      lista->quantidade--;
    }
  }

  free(removido); //Liberamos o espaco de memoria
    
}

// Funcao responsavel por reinserir o ultimoMorto na lista
void reinsere(TLista *lista){

  TElemento *aux, *novo = malloc(sizeof(TElemento));

  novo->id = ultimoMorto[0];
  novo->K = ultimoMorto[1];
  novo->O = 0;
  //Preenchemos o novo elemento com os valores do ultimo elemento removido

  if(novo->id < lista->inicio->id) //Caso onde o elemento a ser inserido esta na cabeca da lista
    insereInicio(lista, ultimoMorto[0], ultimoMorto[1], 0);
  else {
    aux = lista->inicio;
    while (aux->prox != lista->inicio && novo->id > aux->prox->id)
      aux = aux->prox; //Buscamos onde o elemento sera reinserido
    if (aux->prox == lista->inicio) { //Caso onde o elemento a ser inserido esta na cauda da lista
      lista->fim->prox = novo;
      lista->fim = novo;
      novo->prox = lista->inicio;
      lista->quantidade++;
    } else {
      novo->prox = aux->prox;
      aux->prox = novo;
      lista->quantidade++;
    }
  }
}