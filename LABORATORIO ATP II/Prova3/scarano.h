#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct aluno {
    int numero;
    char nome[51];
    float nota[14];
    float exame;
    int frequencia;
    struct aluno *prox;
} Aluno;

typedef struct aula {
    int numero;
    Data data;
    float horas;
    char conteudo[256];
    struct aula *prox;
} Aula;

typedef struct avaliacao {
    char nome[51];
    char tipo;
    Data data;
    float peso;
} Avaliacao;


typedef struct disciplina {
    char *codigo;
    char nome[51];
    int ano, semestre;
    int quantidadeAlunos;
    int provas;
    int trabalhos;
    int horasPrevistas;
    int horasAula;
    int aulasPrevistas;
    int horasRealizadas;
    float notaMinima;
    float frequenciaMinima;
    Avaliacao avaliacoes[14];
    Avaliacao exame;
    Aula *aulas;
    Aluno *alunos;
    struct disciplina *prox;
} Disciplina;

typedef struct professor {
    char nome[51];
    int quantidadeDisciplinas;
    Disciplina *disciplinas;
} Professor;

//Remoção de espaços e underlines
void ajustaStr(char *str) {
    
    int i = 0;
    while (str[i] != '\0') {
        // printf("%c ", retorno[i]);
        if (str[i] == ' ')
            str[i] = '_';
        else if (str[i] == '_')
            str[i] = ' ';

        i++;
    }
}

//Remoção de acentuação
void ajustaStr2(char *str) {
    int i = 0, j, acentos[13] = { -61, -127, -125, -128, -126, -95, -93, -96, -94, -119, -118, -87, -86 };

    while (str[i] != '\0') {
        for (j = 0; j < 13; j++)
            if (acentos[j] == str[i])
                str[i] = '_'; j = 13;

        i++;
    }
}

//Geramos o código da disciplina com a concatenação dos 5 primeiros caracteres, ano - semestre
char *codigoDisciplina(char *str, int sem, int ano) {

    char *aux = malloc(11 * sizeof(char));
    int i;
    char anoStr[5], semStr[2];

    strcpy(aux, "\0");
    strcat(aux, "ABCDE");

    itoa(ano, anoStr, 10);
    itoa(sem, semStr, 10);

    for (i = 0; i < 5 && str[i] != '\0'; i++)
    {
        aux[i] = str[i];
        if (aux[i] == ' ')
            aux[i] = '.';
    }

    strcat(aux, anoStr);
    aux[9] = '-';
    aux[10] = '\0';
    strcat(aux, semStr);
    aux[11] = '\0';

    return aux;
}

// Função para validar se a data inserida é válida. Retorna 1 se for, 0 caso não seja
int validaData (int dia, int mes, int ano) {
    int bissexto;
    //Verifica se o ano é bissexto
    if (!(ano % 4) && ano % 100) {
        bissexto = 1;
    } else if (ano % 4 && !(ano % 400)) {
        bissexto = 1;
    } else {
        bissexto = 0;
    }

    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
        if (dia > 0 && dia <= 31) {
            return 1;
        } else {
            return 0;
        }
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
         if (dia > 0 && dia <= 30) {
            return 1;
        } else {
            return 0;
        }
    }

    if (mes == 2) {
        if (bissexto) {
            if (dia > 0 && dia <= 29) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (dia > 0 && dia <= 28) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

float calculaMedia(Aluno *aluno, Disciplina *disciplina) {

    int i, count = 0, flag = 1;
    float soma = 0, pesos = 0;
    for (i=0; i<14; i++) {
        if (disciplina->avaliacoes[i].tipo != 'N' && aluno->nota[i] != -1) {
            soma += (aluno->nota[i] * disciplina->avaliacoes[i].peso);
            pesos += disciplina->avaliacoes[i].peso;
            count++;
            flag = 0;
        }
    }
    soma = soma/pesos;

    if (flag) //Nao tem média
        return -1;
    else if(soma > 10) //Caso os pesos estejam inválidos e a nota passou de 10
        return 10;
    else if (aluno->exame == -1) //Retorna médoa
        return soma;
    else //Caso o aluno tenha nota de exame, calculamos a média final
        return (soma+(aluno->exame))/2;
}

float calculaFrequencia (Aluno *aluno, Disciplina *disciplina) {
    return (((float)aluno->frequencia/(float)disciplina->aulasPrevistas)*100);
}

int geraCodigoAluno(char *str) {
    int i = 0, aux = 0;
    while (str[i] != '\0') {
        aux += str[i] - '0';
        i++;
    }
    return aux;
}

void flush_in() {
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){}
}

#endif