#include <stdio.h>

#define maxM 20
#define maxN 100

int vetResposta[maxM], combinacoes;

//Prototipos das funcoes usadas
void leitura(int *, int *, int *, int *);
void ordenar(int *, int);
void reseta(int *);
void decompor(int *, int *, int, int, int, int);
void removeUltimo(int *);
void comparaConjuntos(int *);
int comparaNumeros(int *, int);
void printa();

int main() {
  int conjunto[maxM], numeros[maxN], possibilidade[maxM];
  int N, M;
  int i;

  leitura(&N, &M, conjunto, numeros);
  ordenar(conjunto, M);

  for (i = 0; i < N; i++) {
    reseta(possibilidade); //Reset necessario para testarmos novos numeros;
    decompor(conjunto, possibilidade, numeros[i], 0, 0, M);
    printa(); //Printa resultado
  }

  //printf("Pode sorrir?");
  return 0;
} 

//Funcao responsavel pela leitura das variaveis de entrada
void leitura(int *N, int *M, int *conjunto, int *numeros){
  int i;

  scanf("%d %d", &*N, &*M);

  for (i = 0; i < *M; i++) {
    scanf("%d", &conjunto[i]);
  }

  for (i = 0; i < *N; i++) {
    scanf("%d", &numeros[i]);
  }

}

//Funcao para ordenar o conjunto em ordem crescente
void ordenar(int *vet, int max) {
  int i, j, aux;
  for (i = 0; i < max; i++) {
    for (j = i; j < max; j++) {
      if (vet[i] > vet[j]) {
        aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
      }
    }
  }
}



//Funcao chamada para "limpar" tudo para testarmos novos numeros
void reseta(int *possibilidade) {
  int i;
  combinacoes = 0; //Zera quantidade de combinacoes encontradas 
  for (i = 0; i < maxM; i++) {
    //Zera vetores possibilidade e resposta final
    possibilidade[i] = 0;
    vetResposta[i] = 0;
  }
}

//Funcao recursiva com backtracking para decompor um inteiro usando um conjunto de numeros
void decompor(int *conjunto, int *possibilidade, int numero, int i, int soma, int max) {
  int j;
  if(soma == numero) {
    //Encontrada uma combinacao valida
    comparaConjuntos(possibilidade);
    combinacoes++; //Soma uma possibilidade nova
    return; //Sai da recursao
  }
  if(soma > numero || i == max ) {
    return; //Sai da recursao
  }


  //Adicionando o numero conjunto no vetor de possibilidade
  j = 0;
  while (possibilidade[j] != 0) {
    j++;
  }
  possibilidade[j] = conjunto[i];
  possibilidade[j+1] = 0;

  decompor(conjunto, possibilidade, numero, i+1, soma+conjunto[i], max);
  /* A recursao consiste em ir somando na variavel 'soma' o numero do conjunto[i], saindo da recursao em tres casos:
  1- Encontramos um conjunto cuja soma e igual ao numero que buscamos (soma == numero)
  2- A variavel soma ultrapassou o numero que buscamos (soma > numero)
  3- Chegamos no final do vetor conjunto (i == max)
  
  Ao sair da recursao chamamos a funcao removeUltimo*/
  removeUltimo(possibilidade);
  /*Apos remover o ultimo numero do vetor possibilidade chamamos novamente a recursao testando com o 
  proximo indice 'i', por conta do retorno a 'soma' "volta" para o valor anterior*/
  decompor(conjunto, possibilidade, numero, i+1, soma, max); 
}

//Funcao responsavel por remover o ultimo numero do vetor possibilidades
void removeUltimo(int *possibilidade) {
  int i = 0;
  while (possibilidade[i] != 0) {
    i++;
  }
  possibilidade[i-1] = 0; //Removendo podemos testar diferentes combinacoes
}

//Funcao responsavel por comparar os conjuntos 
void comparaConjuntos(int *nova) {
  //Consiste em comparar um novo candiato a ser o maior conjunto com o vetResposta
  int indiceNova, indiceResposta, i;  

  indiceNova = indiceResposta = 0;

  //Somamos os indices ate encontrar o fim do vetor (0)
  while (vetResposta[indiceResposta] != 0 && indiceResposta < maxM)
    indiceResposta++; 
  while (nova[indiceNova] != 0 && indiceNova < maxM)
    indiceNova++;

  if (indiceNova > indiceResposta) {
    //O novo conjunto possui mais elementos que o antigo (vetResposta)
    for (i = 0; i <= indiceNova; i++) {
      vetResposta[i] = nova[i]; //Atualizamos o vetResposta com o novo conjunto
    }
  } else if (indiceNova == indiceResposta) { //Indices iguais -> analisamos qual conjunto tem o maior numero
    if (comparaNumeros(nova, indiceResposta-1)) { 
      for (i = 0; i <= indiceNova; i++) {
        vetResposta[i] = nova[i]; //Atualizamos o vetResposta com o novo conjunto
      }
    }
  } //else: O conjunto antigo tem mais elementos que a nova possibilidade encontrada 
    //OU o conjunto antigo apresenta o numero maior entre os dois
}

//Funcao responsavel por encontrar o maior numero entre dois vetores
int comparaNumeros(int *nova, int indice) {
  /*O retorno e um booleano:
  1 (true): O novo candidato apresenta o maior numero
  0 (false): O vetor antigo apresenta o maior numero*/

  for (; indice >= 0; indice--) {
    if (nova[indice] > vetResposta[indice]) {
      return 1; // O maior numero e do conjunto novo
    } else if (nova[indice] < vetResposta[indice]) {
      return 0; // O maior numero e do conjunto ja salvo
    } // else: segue no for (nova[indice] == vetResposta[indice])
  }

  /*Fim do laco, indica que os vetores comparados sao iguais. Como essa nao e uma possibilidade
  valida o programa nao chega nesta linha porem o return e necessario*/
  return 0; 
}

//Funcao responsavel por imprimir a quantidade de combinacoes e o vetResposta
void printa() {
  int i = 0;

  printf("%d ", combinacoes); //Printa quantidade de combinacoes encontradas
  while (vetResposta[i] != 0 && i < maxM) { //O 0 delimita o fim do vetor
    printf("%d ", vetResposta[i]);
    i++;
  }
  printf("\n");
}