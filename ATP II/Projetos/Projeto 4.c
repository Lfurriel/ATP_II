#include <stdio.h>
#include <stdlib.h>

//Declaracao das structs de lista e elemento da lista
typedef struct elemento {
  int id; //identificacao
  int instante; //instante de chegada
  int tempo; //tempo para atendimento
  struct elemento *prox;
} TElemento;

typedef struct fila {
  TElemento *inicio;
} TFila;

int *centros;

void preencheFila(TFila *, int, int);
void insereOrdenado(TFila *, int, int, int);
void imprimir(TFila, int);
void atendimento(TFila, int, int);
void removeFila(TFila *);


int main() {

  int N, M, i;
  TFila fila;

  scanf("%d %d", &N, &M);

  centros = malloc(M * sizeof(int));
  
  preencheFila(&fila, M, N);
  imprimir(fila, M); //Usado para testes
  atendimento(fila, M, N);

  return 0;    
}

//Funcao responsavel pela leitura de dados
void preencheFila(TFila *fila, int M, int N) {

  int I, O, C, i;

  fila->inicio = NULL; //Inicilaizacao da Fila
  for(i = 0; i < M; i++)
    centros[i] = 0; //Inicializacao dos tempos dos centros

  for(i = 0; i < N; i++) {
    scanf("%d %d %d", &I, &O, &C); //Leitura da entrada
    insereOrdenado(fila, I, O, C);
  }
}

//Funcao responsavel por ordenar os elementos da fila
void insereOrdenado(TFila *fila, int I, int O, int C) {

  /*A ordenacao e feita pelo valor de seu instante de chegada, porem,
  em casos de instantes iguais o criterio de desempate e o id*/

  TElemento *busca, *novo = malloc(sizeof(TElemento));

  int flag = 1;

  novo->id = I;
  novo->instante = O;
  novo->tempo = C;

  if(fila->inicio == NULL) { //Insercao no inicio da Fila, fila nula
    novo->prox = NULL;
    fila->inicio = novo;
  }
  else if(novo->instante < fila->inicio->instante) { // Insercao no inicio da Fila
    //Neste caso o novo instante de chegada e menor que o do elemento no inicio da fila
    novo->prox = fila->inicio;
    fila->inicio = novo;
  }
  else if(novo->instante == fila->inicio->instante && novo->id < fila->inicio->id) { // Instantes iguais devem ser odedenados por ID
    /*Neste caso os instantes de chegada sao iguais porem pelo criterio de desempate,
    o novo elemento deve ser inserido no inicio da fila*/
    novo->prox = fila->inicio;
    fila->inicio = novo;
  }
  else {
    busca = fila->inicio;
    while(busca->prox && (novo->instante >= busca->prox->instante) && flag) {
      if(novo->instante == busca->prox->instante && novo->id < busca->prox->id) // Instantes iguais devem ser odedenados por ID
        flag = 0; //Ao encontrar, paramos o laco while
      else
        busca = busca->prox;
    }
    //Inserimos o elemento novo na fila
    novo->prox = busca->prox;
    busca->prox = novo;
  }
}

//Funcao responsavel por imprimir os valores da fila
void imprimir(TFila fila, int M) {

  TElemento *aux = fila.inicio;
  int i;

  printf("\nFILA:\n");

  while(aux){
    printf("%d %d %d\n", aux->id, aux->instante, aux->tempo); 
    aux = aux->prox;
  }
  printf("\nCAIXAS: ");
  for(i = 0; i < M; i++)
    printf("%d ", centros[i]);
  printf("\n");
}

//Funcao responsavel por atender os elementos da fila
void atendimento(TFila fila, int M, int N) {

  int i;
  int indice, aux; //Variaveis para achar o centro de menor tempo de atendimento

  for(; N > 0; N--) {

    //Bloco para encontrar o centro de menor tempo de atendimento
    indice = 0;
    aux = centros[0];
    for(i = 1; i < M; i++){
      if(centros[i] < aux){
        aux = centros[i];
        indice = i;
      }
    }

    /*Assim como no problema do longestJob caso o novo elemento "chegue depois" do tempo 
    do caixa "andamos" o tempo ate o novo instante*/
    if(centros[indice] < fila.inicio->instante)
      centros[indice] = fila.inicio->instante; 

    centros[indice] += fila.inicio->tempo; //Somamos o tempo de atendimento no centro escolhido
    removeFila(&fila);   
  }

  //Terminado o atendimento de todos elementos da fila, imprimimos os valores de cada centro
  for(i = 0; i < M; i++)
    printf("%d ", centros[i]);
}

void removeFila(TFila *fila) {

  TElemento *removido;
  //Como estamos trabalhando com fila, iremos sempre remover o primeiro elemento
  removido = fila->inicio;
  fila->inicio = fila->inicio->prox;

  free(removido); //Liberamos o espaco de memoria
}

