#include <stdio.h>

#define max 10485760

int main() {

  struct Candidatos {
    int idade;
    int numeroInsc;
    int sexo;
    int anosExp;
  } cand[max];

  int i = 0;
  int mulheresNovas = 0;
  float homens2Anos = 0, idadeMedia = 0, homens = 0, homensVelhos = 0;

  do {
    printf("%d", i);
    printf("\n\nDigite numero de inscricao: ");
    scanf(" %d", &cand[i].numeroInsc);
    if (cand[i].numeroInsc != 0) {
      printf("Digite a idade ");
      scanf("%d", &cand[i].idade);
      printf("Digite sexo (<1> Masculino <2> Feminino): ");
      scanf("%d", &cand[i].sexo);
      printf("Digite anos de experiencia ");
      scanf("%d", &cand[i].anosExp);
      if (cand[i].sexo == 1) {
        homens++;
        if (cand[i].anosExp > 2) {
          homens2Anos++;
          idadeMedia += cand[i].idade;
        }
        if (cand[i].idade > 45) {
          homensVelhos++;
        }
      } else if (cand[i].sexo == 2 && cand[i].idade < 35 &&
                 cand[i].anosExp > 0) {
        mulheresNovas++;
      }
    }
    i++;
  } while (cand[i-1].numeroInsc != 0 && i < max);

  printf("a) idade media dos homens com mais de 2 anos de experiencia: %.2f\n",
         idadeMedia / homens2Anos);
  printf("b) Porcentagem dos homens com mais de 45 anos entre total de homens: "
         "%.2f\n",
         (homensVelhos / homens) * 100);
  printf("c) O numero de mulheres que tem idade inferior a 35 anos e "
         "experiencia: %d\n",
         mulheresNovas);
}