#include <stdio.h>

#define max 30000

typedef struct alunos {
  int id;
  char nome[40];
  char curso[60];
  float nota1, nota2;
} TAluno;

int quantidade = 0;

void escreveArquivo(TAluno *);
void escreveStruct(TAluno *);
void editaStruct(TAluno *);

int main(void) {

  int op;
  TAluno alunos[max];

  do {

    printf("-------------- MENU --------------\n");
    printf("\t1. Editar arquivo\n");
    printf("\t2. Iserir no arquivo\n");
    printf("\t0. Sair\n");

    scanf("%d", &op);

    if (op == 1) {
      editaStruct(alunos);
      escreveArquivo(alunos);
    } else if (op == 2) {
      escreveStruct(alunos);
      escreveArquivo(alunos);
    }

  } while (op != 0);

  return 0;
}

void escreveStruct(TAluno *alunos) {
  int i, op = 1;
  for (i = quantidade; i < max && op != 0; i++) {
    alunos[i].id = i + 1;
    printf("Digite o nome: ");
    scanf(" %s", alunos[i].nome);
    printf("Digite o curso: ");
    scanf(" %s", alunos[i].curso);
    printf("Digite a nota1: ");
    scanf(" %f", &alunos[i].nota1);
    printf("Digite a nota2: ");
    scanf(" %f", &alunos[i].nota2);
    printf("\n");
    quantidade++;
    printf("<0> sair <1> continuar: ");
    scanf("%d", &op);
  }
}

void escreveArquivo(TAluno *alunos) {
  FILE *fp = fopen("ALUNOS.dat", "w");
  int i;
  for (i = 0; i < quantidade; i++) {
    alunos[i].id = i + 1;
    fprintf(fp, "%d ", alunos[i].id);
    fprintf(fp, "%s ", alunos[i].nome);
    fprintf(fp, "%s ", alunos[i].curso);
    fprintf(fp, "%.2f ", alunos[i].nota1);
    fprintf(fp, "%.2f ", alunos[i].nota2);
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void editaStruct(TAluno *alunos) {
  int num, sair;
  do {
    printf("\n\nDigite o numero do aluno que quer editar: ");
    scanf("%d", &num);
    if (num < 1 || num > max) {
      printf("Aluno não encontrado\n\n");
    } else {
      printf("Digite a nova nota1: ");
      scanf(" %f", &alunos[num - 1].nota1);
      printf("Digite a nova nota2: ");
      scanf(" %f", &alunos[num - 1].nota2);
    }

    printf("\n\nEDITADO! SAIR? (0 para sim, 1 para não)\n");
    scanf(" %d", &sair);
  } while (sair != 0);
}
