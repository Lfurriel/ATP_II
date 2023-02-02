#include <stdio.h>
#include <stdlib.h>

int labirinto[25][25];
int semSolucao = 1;

void montaLabirinto(int);
void percorreLabirinto(int, int, int, int, int);

int main() {
  int N, I, C;

  scanf("%d %d %d", &N, &I, &C);
  montaLabirinto(N);
  
  percorreLabirinto(0, I, 0, N, C);

  if(semSolucao)
    printf("-1\n");
  
  return 0;
}

void montaLabirinto(int N) {
  int i, j;

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      scanf("%d", &labirinto[i][j]);
    }
  }
}




void percorreLabirinto(int linha, int coluna, int passos, int N, int C) {
  if (linha == N - 1 && coluna == C && labirinto[linha][coluna] == 0) {
    //Caso final chegamos na ultima linha na coluna da saída
    printf("%d\n", passos);
    semSolucao = 0; //Encontrada solução
  }
  if (!(linha >= 0 && coluna >= 0 && linha < N && coluna < N && labirinto[linha][coluna] == 0))
    return;

  labirinto[linha][coluna] = 1;
  percorreLabirinto(linha+1, coluna, passos+1, N, C); // Desce
  percorreLabirinto(linha, coluna+1, passos+1, N, C); // Anda pra direita
  percorreLabirinto(linha, coluna-1, passos+1, N, C); // Anda pra esquerda

  return;
}
