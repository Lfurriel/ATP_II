/* Escreva um programa para a manipulação de uma lista ligada que contenha
palavras, escritas com caracteres minúsculos. Seu programa deve ter as funçõoes
de inserção e remoção da lista, apresentando seu conteúdo a cada remoção.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 60

typedef struct palavra {
  char palavra[max];
  struct palavra *prox;
} TPalavra;

typedef struct {
  TPalavra *inicio;
  TPalavra *fim;
} TLista;

void iniciaLista(TLista *);
void preencheLista(TLista *, int);
void insereInicio(TLista *, char *);
void insereFim(TLista *, char *);
void insereOrdenado(TLista *, char *);
void imprimirCompleta(TLista);
TPalavra *remover(TLista *, char *);

int main() {
  int N, M, op, i;
  char palavra[max];
  TLista lista;
  TPalavra *remove;

  scanf("%d %d", &N, &M);
  preencheLista(&lista, N);

  for (i = 0; i < M; i++) {
    scanf("%d %s", &op, palavra);
    if (op == 1) {
      insereOrdenado(&lista, palavra);
    } else {
      
      remove = remover(&lista, palavra);
      if (remove) {
        free(remove);
      }
      if (lista.inicio == NULL) {
        printf("NULL\n");
      } else
        imprimirCompleta(lista);
    }
  }

  return 0;
}

// Funcao responsavel por preencher a lista com as variaveis de entrada
void preencheLista(TLista *lista, int N) {
  int i;
  char palavra[max];

  iniciaLista(lista);

  scanf(" %s", palavra);
  insereInicio(lista, palavra); // Primeiro valor a ser preenchido, caso especial

  for (i = 1; i < N; i++) {
    scanf(" %s", palavra);
    insereOrdenado(lista, palavra);
  }
}

// Funcao responsavel por inicializar a lista circular
void iniciaLista(TLista *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
}

// Funcao responsavel por inserir o primeiro valor da lista circular
void insereInicio(TLista *lista, char *palavra) {

  TPalavra *novo = malloc(sizeof(TPalavra));

  strcpy(novo->palavra, palavra);
  novo->prox = lista->inicio;

  lista->inicio = novo;
  if (lista->fim == NULL)
    lista->fim = novo;
  lista->fim->prox = lista->inicio;
}

// Funcao responsavel por inserir um valor na lista circular
void insereFim(TLista *lista, char *palavra) {

  TPalavra *novo = malloc(sizeof(TPalavra));

  strcpy(novo->palavra, palavra);
  lista->fim->prox = novo;
  lista->fim = novo;
  novo->prox = lista->inicio;
}

// Funcao responsavel por adicionar novo elemento de forma ordenada
void insereOrdenado(TLista *lista, char *palavra) {
    TPalavra *aux, *novo = malloc(sizeof(TPalavra));

    strcpy(novo->palavra, palavra);
    if (lista->inicio == NULL) {
        insereInicio(lista, palavra);
     } else if (strcmp(novo->palavra, lista->inicio->palavra) < 0) {
        insereInicio(lista, palavra);
    } else if(strcmp(novo->palavra, lista->inicio->palavra) == 0) {
        return;
    } else {
    aux = lista->inicio;
    while (aux->prox != lista->inicio && (strcmp(novo->palavra, aux->prox->palavra) > 0))
      aux = aux->prox;
    if (aux->prox == lista->inicio && strcmp(novo->palavra, aux->prox->palavra) != 0)
      insereFim(lista, palavra);
    else if(strcmp(novo->palavra, aux->prox->palavra) == 0)
        return;
    else {
      novo->prox = aux->prox;
      aux->prox = novo;
    }
  }
}

// função para remover um nó
TPalavra *remover(TLista *lista, char *palavra) {
  TPalavra *aux, *remover = NULL;

  if (lista->inicio) {
    if (lista->inicio == lista->fim &&
        strcmp(lista->inicio->palavra, palavra) == 0) {
      remover = lista->inicio;
      lista->inicio = NULL;
      lista->fim = NULL;
    } else if (strcmp(lista->inicio->palavra, palavra) == 0) {
      remover = lista->inicio;
      lista->inicio = remover->prox;
      lista->fim->prox = lista->inicio;
    } else {
      aux = lista->inicio;
      while (aux->prox != lista->inicio &&
             (strcmp(aux->prox->palavra, palavra) != 0))
        aux = aux->prox;
      if (strcmp(aux->prox->palavra, palavra) == 0) {
        if (lista->fim == aux->prox) {
          remover = aux->prox;
          aux->prox = remover->prox;
          lista->fim = aux;
        } else {
          remover = aux->prox;
          aux->prox = remover->prox;
        }
      }
    }
  }

  return remover;
}

// Funcao responsavel por imprimir a TODA a lista circular
void imprimirCompleta(TLista lista) {

  TPalavra *palavras = lista.inicio;
  do {

    printf("%s ", palavras->palavra);
    palavras = palavras->prox;
  } while (palavras != lista.inicio);
  printf("\n");
}