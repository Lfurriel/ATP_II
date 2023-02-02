/*GRUPO:
- Bianca Lançoni de Oliveira Garcia
- Gabriel Scarano de Oliveira
- Julia Rodrigues Marques do Nascimento
- Lucas Furriel Rodrigues*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "scarano.h"

// Condições de checagem do SO para a utilização de funções de limpeza do terminal
#ifdef __unix__         
    #include <unistd.h>
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32) 

   #define OS_Windows

   #include <windows.h>

#endif

// Ler arquivos caso o programa já tenha sido utilizado
Professor* lerArquivoProfessor(FILE*, Professor**);        
void lerArquivoDisciplina(Disciplina**);                   

// Funções para a primeira utilização do programa
Professor* preencheProfessor();                            
char* insereDisciplinaOrdenado(Disciplina**);              
Disciplina* lerDisciplina(void);                           
void insereAlunosOrdenado(Aluno**, Aluno*);                


// Escrita do arquivo ao final do programa
void escreveArquivoDisciplinas(char *, Disciplina *);      
void escreveArquivoProfessor(Professor *);                 

// Operações do usuario
Professor* editarProfessor(Professor *);
Professor* editarDisciplina(Professor *);
Disciplina* editarAtributosDisciplina(Professor *);
Professor* editarAluno(Professor*);
Disciplina* alteraAvalicao(Disciplina*, int);
Disciplina* removeDisciplina(Professor*);
int removeAluno(Aluno**, char*);
Aluno* editarAtributosAluno(Disciplina *);

//Opções Menus
int menu (char*);
void cotidiano(Disciplina **);
Aula* lerInfoAula(Disciplina**);
Professor* addNotas(Professor *);
Professor* recuperacao(Professor*);
void fecharSemestre (Disciplina*);

//Relatorios
void relatorioAlunos(Disciplina*);
void relatorioTurmaEspecifica(Professor*);
void relatorioNotas (Professor*);
void relatorioExame(Disciplina*);
void relatorioAprovacao (Professor*);

// Variavel para limpeza do terminal
char clear[6];

//Função principal do programa
int main() {

    #ifdef OS_Windows
        strcpy(clear, "cls");
    #else
        strcpy(clear, "clear");
    #endif

    // 
    setlocale(LC_ALL, "Portuguese");

    // Abertura de arquivo professor
    FILE *arquivo = fopen("Professor.txt", "r");
    Professor *prof;
    Disciplina *busca;
    int op = 1;

    // Caso o arquivo já exista, abrir o existente e guardar suas informações
    if (arquivo)
        prof = lerArquivoProfessor(arquivo, &prof); 
    else // Do contrário, fazer o primeiro cadastro
        prof = preencheProfessor();

    system(clear);

    // Menu
    while (op) {
        op = menu(prof->nome);
        switch (op) {
        case 2:
            cotidiano(&prof->disciplinas);
            break;
        case 3:
            prof = addNotas(prof);
            break;
        case 4:
            fecharSemestre(prof->disciplinas);
            break;
        case 5:
            prof = recuperacao(prof);
            break;
        case 12:
            prof = editarProfessor(prof);
            break;
        case 13:
            prof = editarDisciplina(prof);
            break;
        case 14:
            prof = editarAluno(prof);
            break;
        case 17: //Situação de cada disciplina
            busca = prof->disciplinas;
            while(busca) {
                relatorioAlunos(busca);
                busca = busca->prox;
            }
            break;
        case 18: //Situação de disciplina específica 
            relatorioTurmaEspecifica(prof);
            break;
        case 19: //Notas mínima, máxima e média de cada turma
            relatorioNotas(prof);
            break;
        case 20: //Alunos de exame
            busca = prof->disciplinas;
            while(busca) {
                relatorioExame(busca);
                busca = busca->prox;
                flush_in();
            }
            break;
        case 21: //Aprovados e reprovados de cada turma
            relatorioAprovacao(prof);
            break;
        }
    }
    escreveArquivoProfessor(prof);
    return 0;
} 

//Função responsável por ler o arquivo Professor.txt
Professor* lerArquivoProfessor(FILE *fi, Professor **prof) {
    *prof = malloc(sizeof(Professor));
    char *palavra = malloc(sizeof(char));
    int i;
    Disciplina *aux;

    // Ler arquivo
    /* Foi definido que o nome do professor e o nome e a quantidade das disciplinas seriam inseridos em um único arquivo, 
    e cada disciplina teria seu arquivo separado.*/
    fscanf(fi, "%s", (*prof)->nome);

    // Função para subtituir espaço por underline, e vice-versa
    ajustaStr((*prof)->nome);
    
    // Ler a quantidade de disciplinas
    fscanf(fi, "%d", &(*prof)->quantidadeDisciplinas);

    // Função para ler as disciplinas e guardá-las na lista prof->disciplinas
    (*prof)->disciplinas = NULL;
    for (i = 0; i < (*prof)->quantidadeDisciplinas; i++) {   
        Disciplina *novaDisciplina = malloc(sizeof(Disciplina)), *aux;

        // Recebe o nome da disciplina
        fscanf(fi, "%s", novaDisciplina->nome);
        ajustaStr(novaDisciplina->nome);

        novaDisciplina->prox = NULL;

        // Insere na lista
        if ((*prof)->disciplinas == NULL) {
            (*prof)->disciplinas = novaDisciplina;
        } else {
            aux = (*prof)->disciplinas;
            while (aux->prox)
                aux = aux->prox;
            
            aux->prox = novaDisciplina;
        }
    }

    // Lê o arquivo com o nome da disciplina
    lerArquivoDisciplina(&(*prof)->disciplinas);
    return (*prof);
}

//Função responsável por ler os arquivos das disciplinas, preenchendo a struct Disciplina
void lerArquivoDisciplina(Disciplina** disciplina) {
    Disciplina *aux = *disciplina;
    Aula *aux2, *ant2;
    Aluno *aux3, *ant3;
    char nomeArquivo[60], teste[5];
    FILE *fi;
    int i, oi;

    // While para percorrer a lista de disciplinas
    while (aux != NULL) {
        oi = 0;
        aux->aulas = malloc(sizeof(Aula));
        aux->alunos = malloc(sizeof(Aluno));

        // Copiar o nome do arquivo da lista de disciplinas
        strcpy(nomeArquivo, aux->nome);
        // Ajustar underlines e acentos
        ajustaStr2(nomeArquivo);
        ajustaStr(nomeArquivo);
        strcat(nomeArquivo, ".txt");
        
        // Abrir arquivo da disciplina
        fi = fopen(nomeArquivo, "r");

        // Ler as informações, que foram convencionalmente postas de tal forma no primeiro cadastro
        fscanf(fi, "%d ", &(aux->ano));
        fscanf(fi, "%d ", &(aux->semestre));
        fscanf(fi, "%d ", &(aux->quantidadeAlunos));
        fscanf(fi, "%d ", &(aux->provas));
        fscanf(fi, "%d ", &(aux->trabalhos));
        fscanf(fi, "%d ", &(aux->horasPrevistas));
        fscanf(fi, "%d ", &(aux->horasAula));
        fscanf(fi, "%d ", &(aux->aulasPrevistas));
        fscanf(fi, "%d ", &(aux->horasRealizadas));
        fscanf(fi, "%f ", &(aux->notaMinima));
        fscanf(fi, "%f ", &(aux->frequenciaMinima));

        // Ler informações de provas e trabalhos
        for (i = 0; i < aux->provas + aux->trabalhos; i++) {   
            fscanf(fi, "%s ", aux->avaliacoes[i].nome);
            ajustaStr(aux->avaliacoes[i].nome);
            fscanf(fi, "%c", &(aux->avaliacoes[i].tipo));
            fscanf(fi, "%d", &(aux->avaliacoes[i].data.dia));
            fscanf(fi, "%d", &(aux->avaliacoes[i].data.mes));
            fscanf(fi, "%d", &(aux->avaliacoes[i].data.ano));
            fscanf(fi, "%f", &(aux->avaliacoes[i].peso));
        }  

        // Preencher o resto do vetor com tipo N para indicar espaço vazio
        for (i = aux->provas + aux->trabalhos; i < 15; i++) { 
            aux->avaliacoes[i].tipo = 'N';
        }      

        // Preencher informações de exame
        fscanf(fi, "%s ", aux->exame.nome);
        ajustaStr(aux->exame.nome);
        fscanf(fi, "%c ", &(aux->exame.tipo));
        fscanf(fi, "%d ", &(aux->exame.data.dia));
        fscanf(fi, "%d ", &(aux->exame.data.mes));
        fscanf(fi, "%d ", &(aux->exame.data.ano));
        fscanf(fi, "%f ", &(aux->exame.peso));

        fscanf(fi, "%s", teste);
        fscanf(fi, "%s", teste);
        aux2 = aux->aulas;

        // '/033' usado para separar informações
        while (strcmp(teste, "") != 0) {
            oi = 1;
            fseek(fi, strlen(teste) * (-1), SEEK_CUR);
            fscanf(fi, "%d", &(aux2->numero));
            fscanf(fi, "%d", &(aux2->data.dia));
            fscanf(fi, "%d", &(aux2->data.mes));
            fscanf(fi, "%d", &(aux2->data.ano));
            fscanf(fi, "%f", &(aux2->horas));
            fscanf(fi, "%s", aux2->conteudo);
            ajustaStr(aux2->conteudo);

            // Inserir aulas
            ant2 = aux2;
            aux2 = aux2->prox;
            aux2 = malloc(sizeof(Aula));
            ant2->prox = aux2;
            fscanf(fi, "%s", teste);
        }
        // Caso houve inserção das provas
        if(oi)
            ant2->prox = NULL;
        else
            aux->aulas = NULL;

        fscanf(fi, "%s", teste);
        
        aux3 = aux->alunos;
        
        // Inserção dos alunos e suas notas
        while (strcmp(teste, "") != 0) {
            fseek(fi, strlen(teste) * (-1), SEEK_CUR);
            fscanf(fi, "%d ", &(aux3->numero));
            fscanf(fi, "%s ", aux3->nome);
            ajustaStr(aux3->nome);

            // Preencher notas, depois exame e frequencia
            for (i = 0; i < 14; i++)
                fscanf(fi, "%f ", &(aux3->nota[i]));

            fscanf(fi, "%f ", &(aux3->exame));
            fscanf(fi, "%d ", &(aux3->frequencia));

            // Inserir aluno na lista
            ant3 = aux3;
            aux3 = aux3->prox;
            aux3 = malloc(sizeof(Aluno));
            ant3->prox = aux3;
            fscanf(fi, "%s", teste);
        }
        ant3->prox = NULL;

        // Fechar arquivo
        fclose(fi);
        free(fi);
        aux = aux->prox; // Passar para o arquivo da proxima disciplina
    }
}

//Função responsável por preencher a struct Professor com entradas do usuário
Professor* preencheProfessor() {

    Professor *professor = malloc(sizeof(Professor));
    professor->disciplinas = NULL;
    int i;
    char *nome;

    printf("Insira seu nome: ");
    scanf(" %[^\n]s", professor->nome);
    do { // Recebe a quantidade de disciplinas para inserí-las na lista
        printf("Insira a quantidade de disciplinas: ");
        scanf(" %d", &(professor->quantidadeDisciplinas));
        if (professor->quantidadeDisciplinas > 5) {
            printf("ENTRADA INVÁLIDA, O MÁXIMO PERMITIDO É 5\n");
        }
        if (professor->quantidadeDisciplinas <  1) {
            printf("QUANTIDADE DE DISCIPLINAS INVÁLIDA\n");
        } // Validação da entrada de disciplinas: no minimo 1, no maximo 5
    } while (professor->quantidadeDisciplinas < 1 || professor->quantidadeDisciplinas > 5);
    for (i = 0; i < professor->quantidadeDisciplinas; i++) {
        system(clear);
        nome = insereDisciplinaOrdenado(&professor->disciplinas); // Insere e retorna o nome para informar o cadastro com sucesso
        printf("\n\nDisciplina %s cadastrada!\n", nome);
    }

    return professor;
}

//Função responsável por ordenar alfabeticamente a lista Disciplina
char* insereDisciplinaOrdenado(Disciplina **disciplina) {

    Disciplina *novo = NULL, *aux, *aux_ant;
    int fim = 1;

    novo = lerDisciplina();

    char nome[51];
    strcpy(nome, novo->nome);
    ajustaStr(nome);

    // Lista vazia, inserir no inicio
    if (*disciplina == NULL) {
        *disciplina = novo;
        novo->prox = NULL;
    } // Inserir no inicio
    else if (strcmp(novo->nome, (*disciplina)->nome) <= 0) {
        novo->prox = *disciplina;
        *disciplina = novo;
    } // Inserir no meio ou fim
    else {
        aux = (*disciplina)->prox;
        aux_ant = *disciplina;

        while (aux != NULL) {
            if (strcmp(novo->nome, aux->nome) <= 0) {
                fim = 0;
                novo->prox = aux;
                aux_ant->prox = novo;
            }
            aux_ant = aux;
            aux = aux->prox;
        }
        if(fim) {
            aux_ant->prox = novo;
            novo->prox = NULL;
        }
    }

    return novo->nome;
}

//Função responsável por preencher a struct Disciplina com entradas do usuário
Disciplina* lerDisciplina() {
    Disciplina *novo = malloc(sizeof(Disciplina));
    Aluno *busca;
    int i, aux, numAvaliacoes, validacaoData;
    char opDefault;

    // Inicialização de alunos
    novo->alunos = NULL;
    system(clear);
    printf("Insira o nome da disciplina: ");
    scanf(" %[^\n]s", novo->nome);

    // Inserir ano e semestre da disciplina
    do {
        printf("Insira o ano e o semestre: ");
        scanf(" %d %d", &(novo->ano), &(novo->semestre));
        if (novo->ano < 2013 || novo->ano > 2030) {
            printf("ANO INVÁLIDO\n");
        }
        if (novo->semestre < 1 || novo->semestre > 2) {
            printf("SEMESTRE INVÁLIDO\n");
        }
    } while ((novo->ano < 2013 || novo->ano > 2030) && (novo->semestre < 1 || novo->semestre > 2)); // validação para ano e semestre

    novo->codigo = codigoDisciplina(novo->nome, novo->semestre, novo->ano);

    // Inserir quantidade de alunos matriculados
    do {
        printf("Insira a quantidade de alunos matriculados: ");
        scanf(" %d", &(novo->quantidadeAlunos));
        if (novo->quantidadeAlunos > 50) {
           printf("QUANTIDADE INVÁLIDA, O NÚMERO MÁXIMO DE ALUNOS PERMITIDO É 50\n"); 
        }
        if (novo->quantidadeAlunos < 1) {
            printf("QUANTIDADE INVÁLIDA. O mínimo necessário é 1 aluno por disciplina\n");
        }
    } while(novo->quantidadeAlunos < 1 || novo->quantidadeAlunos > 50);

    // Inserir quantidadade de provas
    do {
        printf("Insira a quantidade de provas: ");
        scanf(" %d", &(novo->provas));
        if (novo->provas > 4) {
            printf("ENTRADA INVÁLIDA, O NÚMERO MÁXIMO DE PROVAS PERMITIDO É 4\n");
        }
        if (novo->provas < 0) {
            printf("QUANTIDADE DE PROVAS INVÁLIDA\n");
        }
    } while (novo->provas > 4 || novo->provas < 0);//Considerei que ele pode não dar nenhuma prova e avaliar só pelo trabalho se quiser

    // Inserir quantidade de trabalhos
    do {
        printf("Insira a quantidade de trabalhos: ");
        scanf(" %d", &(novo->trabalhos));
        if (novo->trabalhos > 10) {
            printf("ENTRADA INVÁLIDA, O NÚMERO MÁXIMO DE TRABALHOS PERMITIDO É 10\n");
        }
        if (novo->trabalhos < 0) {
            printf("QUANTIDADE DE TRABALHOS INVÁLIDA\n");
        }
    } while (novo->trabalhos > 10 || novo->trabalhos < 0);

    // Inserir carga horária
    do {
        printf("Deseja manter a opção default (60 h) para a carga horária?");
        printf("\nDigite 's' para 'sim' e 'n' para 'não': ");
        scanf(" %c", &opDefault);
        if (opDefault == 's' || opDefault == 'S') {
            novo->horasPrevistas = 60;
        } else if (opDefault == 'n' || opDefault == 'N') {
            printf("Insira a carga horária prevista: ");
            scanf(" %d", &(novo->horasPrevistas));
        } else {
            printf("OPÇÃO INVÁLIDA\n");
        }
    } while (opDefault != 's' && opDefault != 'S' && opDefault != 'n' && opDefault != 'N');

    // Inserir hora/aula
    do {
        printf("Insira quantas horas por aula: ");
        scanf(" %d", &(novo->horasAula));
        if(novo->horasAula <= 0 || novo->horasAula > novo->horasPrevistas)
            printf("OPÇÃO INVÁLIDA\n");    
    } while (novo->horasAula <= 0 || novo->horasAula > novo->horasPrevistas);

    novo->aulasPrevistas = novo->horasPrevistas/novo->horasAula;
    novo->horasRealizadas = 0;

    // Inserir nota mínima
    do {
        printf("Deseja manter a opção default para a nota mínima de aprovação (5.00)?");
        printf("\nDigite 's' para 'sim' e 'n' para 'não': ");
        scanf(" %c", &opDefault);
        if (opDefault == 's' || opDefault == 'S') {
            novo->notaMinima = 5;
        } else if (opDefault == 'n' || opDefault == 'N') {
            printf("Insira a nota mínima para aprovação: ");
            scanf(" %f", &(novo->notaMinima));
            if (novo->notaMinima > 10 || novo->notaMinima < 0)
                printf("OPÇÃO INVÁLIDA\n");
        } else {
            printf("OPÇÃO INVÁLIDA\n");
        }
    } while ((opDefault != 's' && opDefault != 'S' && opDefault != 'n' && opDefault != 'N') || novo->notaMinima < 0 || novo->notaMinima > 10);

    // Inserir porcentagem de frequência mínima
     do {
        printf("Deseja manter a opção default para a frequência mínima para aprovação (70%%)?");
        printf("\nDigite 's' para 'sim' e 'n' para 'não': ");
        scanf(" %c", &opDefault);
        if (opDefault == 's' || opDefault == 'S') {
            novo->frequenciaMinima = 70;
        } else if (opDefault == 'n' || opDefault == 'N') {
            printf("Insira o percentual mínimo de frequência para aprovação: ");
            scanf(" %f", &(novo->frequenciaMinima));
            if (novo->frequenciaMinima > 100 || novo->frequenciaMinima < 0)
                printf("OPÇÃO INVÁLIDA\n");
        } else {
            printf("OPÇÃO INVÁLIDA\n");
        }
    } while ((opDefault != 's' && opDefault != 'S' && opDefault != 'n' && opDefault != 'N') || (novo->frequenciaMinima > 100 || novo->frequenciaMinima < 0));
    
    system(clear);
    novo->aulas = NULL;
    numAvaliacoes = novo->trabalhos + novo->provas;


    // Inserir informações das avaliações
    for (i = 0; i < numAvaliacoes; i++) {
        printf("\n\nINFORMAÇÕES DA AVALIAÇÃO %d\n", i + 1);
        printf("Insira o nome da avaliação: ");
        scanf(" %[^\n]s", novo->avaliacoes[i].nome);

        do {
            printf("Insira o tipo de avaliação (P para prova e T para trabalho): ");
            scanf(" %c", &(novo->avaliacoes[i].tipo));
            if (novo->avaliacoes[i].tipo != 'P' && novo->avaliacoes[i].tipo != 'p' && novo->avaliacoes[i].tipo != 'T' && novo->avaliacoes[i].tipo != 't') {
                printf("OPÇÃO INVÁLIDA\n");
            }
        } while (novo->avaliacoes[i].tipo != 'P' && novo->avaliacoes[i].tipo != 'p' && novo->avaliacoes[i].tipo != 'T' && novo->avaliacoes[i].tipo != 't');

        do {
            printf("Insira a data da avalição (DD MM): ");
            novo->avaliacoes[i].data.ano = novo->ano;
            scanf("%d %d", &(novo->avaliacoes[i].data.dia), &(novo->avaliacoes[i].data.mes));
            validacaoData = validaData(novo->avaliacoes[i].data.dia, novo->avaliacoes[i].data.mes, novo->ano);
             if (validacaoData == 0) {
                printf("DATA INVÁLIDA\n");
            }
        } while (validacaoData == 0);

        do {
            printf("Insira o peso da avaliação: ");
            scanf(" %f", &(novo->avaliacoes[i].peso));
            if (novo->avaliacoes[i].peso <= 0 || novo->avaliacoes[i].peso > 100)
                printf("PESO INVÁLIDO\n");
        } while (novo->avaliacoes[i].peso <= 0 || novo->avaliacoes[i].peso > 100);
    }

    // Preencher o resto do vetor com valores default
    for (i = numAvaliacoes; i < 14; i++) {
        strcpy(novo->avaliacoes[i].nome, "default!-@");
        novo->avaliacoes[i].tipo = 'N';
        novo->avaliacoes[i].data.dia = 99;
        novo->avaliacoes[i].data.mes = 99;
        novo->avaliacoes[i].data.ano = 9999;
        novo->avaliacoes[i].peso = -1;
    }

    system(clear);

    // Preencher informações do exame
    printf("INFORMAÇÕES DO EXAME\n");
    strcpy(novo->exame.nome, "EXAME");
    novo->exame.tipo = 'E';
    do {
        printf("Insira a data do exame (DD MM): ");
        novo->exame.data.ano = novo->ano;
        scanf("%d %d", &(novo->exame.data.dia), &(novo->exame.data.mes));
        validacaoData = validaData(novo->exame.data.dia, novo->exame.data.mes, novo->ano);
        if (validacaoData == 0) {
            printf("DATA INVÁLIDA\n");
        }
    }  while (validacaoData == 0);
    novo->exame.peso = 50;

    // Inserir lista de alunos
    aux = novo->quantidadeAlunos;
    printf("Insira os nomes dos alunos matriculados: ");
    for (i = 0; i < aux; i++)
        insereAlunosOrdenado(&(novo->alunos), NULL);

    novo->prox = NULL;
    system(clear);
    return novo;
}

//Função responsável por ordenar alfabeticamente a lista Aluno
void insereAlunosOrdenado(Aluno **aluno, Aluno *novo) {

    Aluno *aux, *aux_ant;
    int i;

    if(novo == NULL) { //Caso NULL estamos preenchendo um NOVO aluno
        // Preencher o nome e o restante com valores default
        novo = malloc(sizeof(Aluno));
        printf("\n- ");
        scanf(" %[^\n]s", novo->nome);
        for (i = 0; i < 14; i++)
            novo->nota[i] = -1; // -1 indica que essa nota não foi preenchida
        novo->exame = -1;
        novo->numero = geraCodigoAluno(novo->nome); // Função para gerar código único do aluno
        novo->frequencia = 0;
    } //Caso já preenchido apenas o inserimos na lista novamente (mudança de nome)    

    // Inserir na lista vazia
    if (*aluno == NULL) {
        *aluno = novo;
        novo->prox = NULL;
        return;
    }

    // Inserir antes do inicio
    if (strcmp(novo->nome, (*aluno)->nome) <= 0) {
        novo->prox = *aluno;
        *aluno = novo;
        return;
    }

    // Inserir no meio e no fim
    aux = (*aluno)->prox;
    aux_ant = *aluno;

    while (aux != NULL) {
        if (strcmp(novo->nome, aux->nome) <= 0) {
            aux_ant->prox = novo;
            novo->prox = aux;
            return;
        }
        aux_ant = aux;
        aux = aux->prox;
    }
    
    aux_ant->prox = novo;
    novo->prox = NULL;
}

//Função responsável por escrever o arquivo 'NomeDisciplina'.txt
void escreveArquivoDisciplinas(char *nome, Disciplina *disciplina) { 
 
    int aux, i, j;
    char nomeArquivo[60];
    strcpy(nomeArquivo, nome);
    strcat(nomeArquivo, ".txt");

    Aluno *aluno = disciplina->alunos;
    Aula *aula = disciplina->aulas;
    ajustaStr2(nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "w");

    // Escrever todas as informações da disciplina no arquivo
    fprintf(arquivo, "%d ", disciplina->ano);
    fprintf(arquivo, "%d ", disciplina->semestre);
    fprintf(arquivo, "%d ", disciplina->quantidadeAlunos);
    fprintf(arquivo, "%d ", disciplina->provas);
    fprintf(arquivo, "%d ", disciplina->trabalhos);
    fprintf(arquivo, "%d ", disciplina->horasPrevistas);
    fprintf(arquivo, "%d ", disciplina->horasAula);
    fprintf(arquivo, "%d ", disciplina->aulasPrevistas);
    fprintf(arquivo, "%d ", disciplina->horasRealizadas);
    fprintf(arquivo, "%.2f ", disciplina->notaMinima);
    fprintf(arquivo, "%.2f ", disciplina->frequenciaMinima);
    fprintf(arquivo, "\n");

    


    // Escrever as informações das possíveis 14 avaliações (apenas caso o tipo seja diferente de N, ou seja, não tenha sido retirada ou não existe)
    for (i = 0; i < 14; i++) {
        if(disciplina->avaliacoes[i].tipo != 'N') {
            ajustaStr(disciplina->avaliacoes[i].nome);
            fprintf(arquivo, "%s ", disciplina->avaliacoes[i].nome);
            fprintf(arquivo, "%c ", disciplina->avaliacoes[i].tipo);
            fprintf(arquivo, "%d ", disciplina->avaliacoes[i].data.dia);
            fprintf(arquivo, "%d ", disciplina->avaliacoes[i].data.mes);
            fprintf(arquivo, "%d ", disciplina->avaliacoes[i].data.ano);
            fprintf(arquivo, "%.2f ", disciplina->avaliacoes[i].peso);
            fprintf(arquivo, "\n");
        }
    }

    //Escrever informações do exame
    fprintf(arquivo, "%s ", disciplina->exame.nome);
    fprintf(arquivo, "%c ", disciplina->exame.tipo);
    fprintf(arquivo, "%d ", disciplina->exame.data.dia);
    fprintf(arquivo, "%d ", disciplina->exame.data.mes);
    fprintf(arquivo, "%d ", disciplina->exame.data.ano);
    fprintf(arquivo, "%.2f ", disciplina->exame.peso);
    fprintf(arquivo, "\n");

    // Caractere especial para separação das informações
    fprintf(arquivo, "%c\n", 27);

    // Escrever aulas
    while (aula) {
        fprintf(arquivo, "%d ", aula->numero);
        fprintf(arquivo, "%d ", aula->data.dia);
        fprintf(arquivo, "%d ", aula->data.mes);
        fprintf(arquivo, "%d ", aula->data.ano);
        fprintf(arquivo, "%f ", aula->horas);
        ajustaStr(aula->conteudo);
        fprintf(arquivo, "%s ", aula->conteudo);
        aula = aula->prox;
        fprintf(arquivo, "\n");

    }

    fprintf(arquivo, "%c\n", 27);


    // Escrever informações dos alunos
    while (aluno) {
        fprintf(arquivo, "%d ", aluno->numero);
        ajustaStr(aluno->nome);
        fprintf(arquivo, "%s ", aluno->nome);

        for (i = 0; i < 14; i++)
            fprintf(arquivo, "%.2f ", aluno->nota[i]);
        fprintf(arquivo, "%.2f ", aluno->exame);
        fprintf(arquivo, "%d ", aluno->frequencia);
        fprintf(arquivo, "\n");
        aluno = aluno->prox;
    }
    // Caractere de separação
    fprintf(arquivo, "%c\n", 27);
    // Fechar arquivo
    fclose(arquivo);
    free(arquivo);
}

//Função responsável por escrever o arquivo Professor.txt 
void escreveArquivoProfessor(Professor *professor) {

    FILE *arquivo = fopen("Professor.txt", "w");
    Disciplina *disciplina = professor->disciplinas;

    // Escreve nome sem espaços e a quantidade de disciplinas
    ajustaStr(professor->nome);
    fprintf(arquivo, "%s ", professor->nome);
    fprintf(arquivo, "%d ", professor->quantidadeDisciplinas);
    fprintf(arquivo, "\n");

    // Escreve nomes das disciplinas
    while (disciplina) {
        ajustaStr(disciplina->nome);
        fprintf(arquivo, "%s ", disciplina->nome);
        escreveArquivoDisciplinas(disciplina->nome, disciplina);
        disciplina = disciplina->prox;
    }

    fprintf(arquivo, "\n");

    // Fecha arquivo
    fclose(arquivo);
    free(arquivo);
}

//Função de Menu inicial
int menu(char *nome) {
    int op, aux;
    system(clear);

    printf("\tOlá, bem-vindo(a) professor(a) %s\n\n", nome);
    do {
        printf("\n\t\t\tMENU:\n\tInsira o número da operação a ser realizada:\n\n");
        printf("\t 1 - Editar informações\n");
        printf("\t 2 - Cotidiano\n");
        printf("\t 3 - Adicionar notas de avaliação\n");
        printf("\t 4 - Final do semestre\n");
        printf("\t 5 - Recuperação\n");
        printf("\t 6 - Relatórios\n");
        printf("\t 0 - Sair do programa\n\n\tOpção: ");
        scanf("%d", &op);
        if (op < 0 || op > 6)
            printf("ENTRADA INVÁLIDA!\n");
    } while (op < 0 || op > 6);


    if (op == 1) { // Editar informações
        do {
            system(clear);
            printf("\n\tQual informação deseja editar?\n");
            printf("\t 1 - Editar professor\n");
            printf("\t 2 - Editar disciplina\n");
            printf("\t 3 - Editar aluno\n");
            printf("\t 0 -  Voltar\n\n\tOpção: ");
            scanf("%d", &aux);
            if (aux < 0 || aux > 3)
                printf("ENTRADA INVÁLIDA!\n");
        } while (aux < 0 || aux > 3);
        op = op + aux + 10;
    }
    else if (op == 6) { //RELATÓRIOS
        do {
            system(clear);
            printf("\n\tQual relatório deseja imprimir?\n");
            printf("\t 1 - Situação de cada disciplina\n");
            printf("\t 2 - Situação de uma disciplina específica\n");
            printf("\t 3 - Notas mínima, média e máxima de cada turma\n");
            printf("\t 4 - Relação de alunos de exame para cada turma\n"); // assumimos que é para cada turma
            printf("\t 5 - Aprovados e reprovados de uma turma\n");
            printf("\t 0 -  Voltar\n");
            printf("\n\tOpção: ");
            scanf("%d", &aux);
            if (aux < 0 || aux > 5)
                printf("ENTRADA INVÁLIDA!\n");
        } while (aux < 0 || aux > 5);
        op = op + aux + 10;
    }
    if (op == 11 || op == 16) // Usuário pressionou 1 ou 6 e depois 0 (voltar), chamando menu novamente
        return menu(nome);
    else
        return op;
}

//Função responsável por editar a struct Professor
Professor* editarProfessor(Professor *prof) {

    int op;

    system(clear);
    printf("\n\n\t\tEditar nome do professor?\n"); //Optamos por, neste menu, mudar apenas o nome do professor
    do {
        printf("\t\t1 - Sim\n");
        printf("\t\t2 - Cancelar\n");
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if (op != 1 && op != 2)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op != 1 && op != 2); //Validação de entrada
    if (op == 1) {
        system(clear);
        printf("\tInsira o novo nome: ");
        scanf(" %[^\n]s", prof->nome); //Le o novo nome do professor
    }

    return prof;
}

//Função responsável por editar a struct Disciplina
Professor* editarDisciplina(Professor *prof) {

    Professor *aux = prof;
    int op;
    system(clear);
    printf("\n\n\t\tInsira o número da operação a ser realizada:\n");
    do {
        printf("\t\t1 - Adicionar disciplina\n");
        printf("\t\t2 - Remover disciplina\n");
        printf("\t\t3 - Editar atributos de uma disciplina\n");
        printf("\t\t0 - Sair\n");
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if (op < 0 || op > 3)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > 3); //Validação de entrada
    if (op == 0) {
        return aux;
    } else if (op == 1) {
        if (aux->quantidadeDisciplinas == 5) {
            printf("Número máximo de disciplinas já atingido\n");
        } else {
            insereDisciplinaOrdenado(&aux->disciplinas); //Chama função que insere uma nova disciplina
            aux->quantidadeDisciplinas++; //Aumenta a quantidade de disciplina na struct Professor
        }
    } else if (op == 2) {
        if (aux->quantidadeDisciplinas == 0) { //Validação se existe disciplina a ser removida
            printf("Não há disciplinas para remover\n");
        } else {
            aux->disciplinas = removeDisciplina(aux); //Chama a função responsável por remover a disciplina da lista
        }
    } else if (op == 3) {
        if (aux->quantidadeDisciplinas == 0) { //Validação se há disciplina para ser editada
            printf("Não há disciplinas para alterar\n");
        } else {
            aux->disciplinas = editarAtributosDisciplina(aux); //Chama função responsável por editar campos da disciplina
        }
    }
    
    return aux;
}

//Função responsável por editar os campos da struct Disciplina
Disciplina* editarAtributosDisciplina(Professor *prof) {

    Disciplina *disciplina = prof->disciplinas; //Head da lista disciplina
    Disciplina *busca = prof->disciplinas;

    char aux[51];
    int flag = 0, i = 1, op;

    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome); //Apresenta todas as discipinas existentes
        busca = busca->prox;
        i++;
    }
    printf("\t\t 0 - Voltar");
    i--;
    do {
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i); //Validação de entrada

    if(op == 0)
        return disciplina; //Opção de voltar, retorna apenas a cabeça

    busca = disciplina;
    for(i = 1; i < op; i++)
        busca = busca->prox; //Ponteiro busca caminha até a disciplina selecionada

    system(clear);
    do {
        printf("\n\n\t\tQual atributo deseja editar?\n");
        printf("\t\t 1 - Nome da disciplina (\"%s\")\n", busca->nome);
        printf("\t\t 2 - Ano - Semestre (\"%d-%d\")\n", busca->ano, busca->semestre);
        printf("\t\t 3 - Adicionar/remover provas (\"%d\")\n", busca->provas);
        printf("\t\t 4 - Adicionar/remover trabalhos (\"%d\")\n", busca->trabalhos);
        printf("\t\t 5 - Editar exame\n");
        printf("\t\t 6 - Carga horária prevista (\"%d\")\n", busca->horasPrevistas);
        printf("\t\t 7 - Nota mínima para aprovação (\"%.2f\")\n", busca->notaMinima);
        printf("\t\t 8 - Frequência mínima (\"%.2f\")\n", busca->frequenciaMinima);
        printf("\t\t 0 - Sair\n");

        printf("\n\tOpção: ");
        scanf("%d", &op);

        if(op < 0 || op > 8)
            printf("RESPOSTA INVÁLIDA!\n\n");

    } while(op < 0 || op > 8); //Validação de entrada

    strcpy(aux, busca->nome);
    ajustaStr(aux);

    if(op == 0)
        return disciplina; //Opção de voltar, retorna apenas a cabeça
    else if(op == 1) {
        system(clear);
        printf("Insira o novo nome da disciplina: ");
        scanf(" %[^\n]s", busca->nome); //Le o novo nome da disciplina
        strcpy(aux, busca->nome);
        busca->codigo = codigoDisciplina(aux, busca->semestre, busca->ano); //Altera o código da disciplina
    } else if (op == 2) {
        system(clear);
        do {
            printf("Insira o novo ano e novo semestre: ");
            scanf("%d %d", &busca->ano, &busca->semestre); //Le o novo ano e semestre
            if (busca->ano < 2013 || busca->ano > 2030) {
                printf("ANO INVÁLIDO\n");
            }
            if (busca->semestre < 1 || busca->semestre > 2) {
                printf("SEMESTRE INVÁLIDO\n");
            }
        } while ((busca->ano < 2013 || busca->ano > 2030) || (busca->semestre < 1 || busca->semestre > 2)); //Validação de entrada

        strcpy(aux, busca->nome);
        busca->codigo = codigoDisciplina(aux, busca->semestre, busca->ano); //Altera o código da disciplina
    
    } else if (op == 3 || op == 4 || op == 5) {
        busca = alteraAvalicao(busca, op); //Chama a função para alterar campos da struct Avaliacao

    } else if (op == 6) {
            system(clear);
        do {
            printf("Insira a nova carga horária: ");
            scanf(" %d", &busca->horasPrevistas);
            busca->aulasPrevistas = busca->horasPrevistas/busca->horasAula;
            
        } while (busca->horasPrevistas < 0); //Validação de entrada

    } else if (op == 7) {
            system(clear);
         do {
            printf("Insira a nova nota mínima para aprovação: ");
                scanf(" %f", &busca->notaMinima);  
            if (busca->notaMinima > 10 || busca->notaMinima < 0) {
                printf("OPÇÃO INVÁLIDA\n");
            }
        } while (busca->notaMinima > 10 || busca->notaMinima < 0); //Validação de entrada
   
    } else if (op == 8) {
            system(clear);
         do {
            printf("Insira a nova frequência mínima de aprovação: ");
            scanf(" %f", &busca->frequenciaMinima);
            if (busca->frequenciaMinima < 0 || busca->frequenciaMinima > 100)
                printf("OPÇÃO INVÁLIDA\n");
    
        } while (busca->frequenciaMinima < 0 || busca->frequenciaMinima > 100); //Validação de entrada
    }

    return disciplina;
}

//Função responsável por editar atributos da struct Avaliacao
Disciplina* alteraAvalicao(Disciplina* disciplina, int op) {

    int i, OP, id, count = 0, flag = 1, dia, mes, ano, validacaoData;
    char aux[51], c;
    float peso;

    //Com o parametro int op sabemos o que o usuário está alterando 
    if (op == 3)
        c = 'P'; //Prova
    else if (op == 4)
        c = 'T'; //Trabalho
    else
        c = 'E'; //Exame

    system(clear);
    printf("\n\t\tOperação a ser realizada\n\n\t1- Editar\n\t2- Adicionar\n\t3- Excluir\n");
    printf("\n\tOpção: ");
    do
    {
        scanf("%d", &OP);
        if (OP < 1 || OP > 3)
            printf("OPÇÃO INVÁLIDA!\n");
    } while (OP < 1 || OP > 3); //Validação de entrada


    if (op == 3 && (OP == 1 || OP == 3) && disciplina->provas == 0) {
        printf("Não há provas para serem modificadas.\n");
        return disciplina;
    }
    else if (op == 4 && (OP == 1 || OP == 3) && disciplina->trabalhos == 0) {
        printf("Não há trabalhos para serem modificados.\n");
        return disciplina;
    }

    if (op != 5 && OP != 2) { // provas e trabalhos
        system(clear);
        printf("\n\n\t\tSelecione:\n");
        i=0;
        for(i = 0; i < 14; i++) {
            if(disciplina->avaliacoes[i].tipo == c) { //Apresenta todas as avaliações do tipo c
                printf("\t\t %d - %s - %d/%d/%d\n", count+1, disciplina->avaliacoes[i].nome, disciplina->avaliacoes[i].data.dia, disciplina->avaliacoes[i].data.mes, disciplina->avaliacoes[i].data.ano); //Apresentar a data tbm?
                count++;
            }
        }
        do {
            printf("\n\tOpção: ");
            scanf("%d", &id);
            if (id < 1 || id > count)
                printf("OPÇÃO INVÁLIDA!\n");
        } while (id < 1 || id > count); //Validação de entrada

        //O bloco abaixo é para buscar o índice da opção selecionada
        count = 0;
        for (i=0; i < 15 && flag; i++) {
            if(disciplina->avaliacoes[i].tipo == c) {
                count++;
                if (count == id)
                    flag = 0;
            }
        }
        i--;


        if (OP == 1) {
            system(clear);
            printf("\tO que deseja editar?\n");
            printf("1 - Nome\n");
            printf("2 - Data\n");
            printf("3 - Peso\n");
            printf("Opção: ");

            do {
                scanf("%d", &id);
                if (id < 1 || id > 3)
                    printf("OPÇÃO INVÁLIDA!\n");
            } while (id < 1 || id > 3); //Validação de entrada

            if (id == 1) {
                printf("\nNome: ");
                scanf(" %[^\n]s", aux);
                strcpy(disciplina->avaliacoes[i].nome, aux); 
            } 
            else if (id == 2) {
                do {   
                    printf("Insira a nova data (DD MM AAAA): ");
                    scanf("%d %d %d", &dia, &mes, &ano);
                    validacaoData = validaData(dia, mes, ano);
                    if (validacaoData == 0 || ano < 2013 || ano > 2030)
                        printf("DATA INVÁLIDA!\n");
                } while (validacaoData == 0 || ano < 2013 || ano > 2030);
                disciplina->avaliacoes[i].data.dia = dia;
                disciplina->avaliacoes[i].data.mes = mes;
                disciplina->avaliacoes[i].data.ano = ano;
            } 
            else {
                printf("\nPeso: ");
                do {
                    scanf("%f", &peso);
                    if (peso < 0 || peso > 100)
                        printf("QUANTIA INVÁLIDA!\n");
                } while (peso < 0 || peso > 100); //Validação de entrada
                disciplina->avaliacoes[i].peso = peso;
            }
        }
        else {
            if(op == 3)
                disciplina->provas--;
            else
                disciplina->trabalhos--;
            disciplina->avaliacoes[i].tipo = 'N'; //Setamos o tipo para N, isso é, avaliação cancelada/não existente
        }
    } else if (OP == 2) {

        //Conta quantas avaliações existem  
        for (i=0; i<15 && flag; i++) {
            if (disciplina->avaliacoes[i].tipo == 'N')
                flag = 0;
        }
        i--;

        if (flag == 1) {
            printf("Número máximo de métodos avaliativos atingido! Exclua para poder adicionar\n\n");
            return disciplina;
        }
        printf("\n\n\tAdicionar ");
        if (c == 'P') {
            printf("prova\n");
            disciplina->provas++;
        }
        else {
            printf("trabalho\n");
            disciplina->trabalhos++;
        }
        printf("Nome: ");
        scanf(" %[^\n]s", aux);
        do {
            printf("Data (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);
            validacaoData = validaData(dia, mes, ano);
            if (validacaoData == 0 || ano < 2013 || ano > 2030)
                printf("DATA INVÁLIDA!\n");
        } while (validacaoData == 0 || ano < 2013 || ano > 2030);
        printf("Peso: ");
        do {
            scanf("%f", &peso);
            if (peso < 0 || peso > 100)
                printf("QUANTIA INVÁLIDA!\n");
        } while (peso < 0 || peso > 100);

        strcpy(disciplina->avaliacoes[i].nome, aux);
        disciplina->avaliacoes[i].tipo = c;
        disciplina->avaliacoes[i].data.dia = dia;
        disciplina->avaliacoes[i].data.mes = mes;
        disciplina->avaliacoes[i].data.ano = ano;
        disciplina->avaliacoes[i].peso = peso;
    } else {

        /*Edição de exame - só é possível alterar a data*/
        printf("\n\n\t\tEdição de exame:\n");
        i = 0;
        while(flag) {
            if(disciplina->avaliacoes[i].tipo == 'E') {
                printf("\t\t %d - %s - %d/%d/%d\n", count+1, disciplina->avaliacoes[i].nome, disciplina->avaliacoes[i].data.dia, disciplina->avaliacoes[i].data.mes, disciplina->avaliacoes[i].data.ano); //Apresentar a data tbm?
                flag = 0;
            }
            i++;
        }
        i--;

        do
        {
            printf("Insira a nova data (DD MM AAAA): ");
            scanf("%d %d %d", &dia, &mes, &ano);
            validacaoData = validaData(dia, mes, ano);
            if (validacaoData == 0 || (ano < 2013 || ano > 2030))
                printf("DATA INVÁLIDA!\n");
        } while (validacaoData == 0 || (ano < 2013 || ano > 2030));
        disciplina->avaliacoes[i].data.dia = dia;
        disciplina->avaliacoes[i].data.mes = mes;
        disciplina->avaliacoes[i].data.ano = ano;
    }

    return disciplina;
}

//Função responsável por editar a struct Aluno
Professor* editarAluno(Professor *prof) {

    Professor *aux = prof;

    Disciplina *disciplina = prof->disciplinas, *busca = prof->disciplinas;
    int flag = 0, i = 1, op;
    char nome[51];

    /*Bloco abaixo é responsável por buscar a disciplina na qual o aluno
    que iremos editar se encontra*/
    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome);
        busca = busca->prox;
        i++;
    }
    printf("\t\t 0 - Voltar");
    i--;
    do {
        printf("\n\n\t Opção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i);

    if(op == 0)
        return prof;

    busca = disciplina;
    for(i = 1; i < op; i++)
        busca = busca->prox;

    //Após selecionar a disciplina apresentamos o menu com as opções de edição
    system(clear);
    printf("\n\n\t\tInsira o número da operação a ser realizada:\n");
    do {
        printf("\t\t1 - Adicionar aluno\n");
        printf("\t\t2 - Remover aluno\n");
        printf("\t\t3 - Editar atributos de um aluno\n");
        printf("\t\t0 - Sair\n");
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if (op < 0 || op > 3)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > 3); //Validação de entrada

    if (op == 0)
        return aux; //Opção de sair
    else if (op == 1) {
        if (busca->quantidadeAlunos == 50) { 
            printf("Número máximo de alunos já atingido\n"); //Não é possível adicionar mais alunos
        } else {
            printf("Insira o nome do novo aluno: ");
            insereAlunosOrdenado(&busca->alunos, NULL); //Chama função de inserir um NOVO aluno
            busca->quantidadeAlunos++; //Aumenta a quantidade de alunos naquela disciplina
        }
    }
    else if (op == 2) {
        if (busca->quantidadeAlunos == 0) {
            printf("Não há alunos matriculados nesta disciplina\n"); //Não existe aluno para remover
        } else {

            printf("Insira o nome do aluno a ser removido: ");
            scanf(" %[^\n]s", nome);
            if (removeAluno(&busca->alunos, nome)) //Busca por nome o aluno a ser removido
                busca->quantidadeAlunos--; //Caso removido com sucesso, diminuimos a quantidade de alunos na disciplina
        }
    }
    else if (op == 3) {
        if (busca->quantidadeAlunos == 0) {
            printf("Não há alunos matriculados nesta disciplina\n"); //Não existe aluno para editar
        } else {
            busca->alunos = editarAtributosAluno(busca); //Chama função de editar atributos do aluno
        }
    }
    
    return aux;
 
}

//Função responsável por editar campos da struct Aluno
Aluno* editarAtributosAluno(Disciplina* disciplina) {

    Aluno *novo, *aux2, *aluno = disciplina->alunos, *busca = disciplina->alunos;
    novo = malloc(sizeof(Aluno));
    char *aux = malloc(51*sizeof(char));
    strcpy(aux, disciplina->nome);
    int flag = 0, i = 1, op, count;
    char nome[51];

    /*Bloco a seguir é responsável por apresentar a lista de alunos e ler
    qual o usuário ira editar*/
    system(clear);
    printf("\n\n\t\tSelecione o aluno:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome);
        busca = busca->prox;
        i++;
    }
    i--;
    do {
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if(op < 1 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 1 || op > i); //Validação de entrada

    busca = disciplina->alunos;
    for(i = 1; i < op; i++)
        busca = busca->prox;

    do {
        system(clear);
        printf("\n\n\t\tQual atributo deseja editar?\n");
        printf("\t\t 1 - Nome do aluno (\"%s\")\n", busca->nome);
        printf("\t\t 2 - Notas\n");
        printf("\t\t 3 - Nota exame\n");
        printf("\t\t 0 - Sair\n");

        printf("\n\tOpção: ");
        scanf("%d", &op);

        if(op < 0 || op > 3)
            printf("RESPOSTA INVÁLIDA!\n\n");

    } while(op < 0 || op > 3); //Validação de entrada

    if(op == 0)
        return aluno; //Sair
    else if(op == 1) {
        //Copia informações do aluno para variavel nova
        system(clear);
        novo->exame = busca->exame;
        for (i=0; i<14; i++) 
            novo->nota[i] = busca->nota[i];
        novo->numero = busca->numero;
        
        printf("Insira o novo nome do aluno: ");
        scanf(" %[^\n]s", novo->nome); //le o novo nome

        strcpy(nome, busca->nome);
        if (removeAluno(&aluno, nome)) // remove da lista o "antigo" aluno
            insereAlunosOrdenado(&aluno, novo); //caso remoção tenha ocorrido com sucesso insere o "novo" aluno renomeado
        
    } else if (op == 2) {
        do {
            //Bloco a seguir apresenta todas as provas aplicadas da disciplina selecionada
            system(clear);
            count = 1;
            printf("\n\n\t\tSelecione a nota:\n");
            for(i = 0; i< 14; i++) {
                if(disciplina->avaliacoes[i].tipo != 'N') {
                    if (busca->nota[i] != -1)
                        printf("\t\t%d - %s: %.2f\n", count, disciplina->avaliacoes[i].nome, busca->nota[i]);
                    else
                        printf("\t\t%d - %s: Prova ainda não aplicada\n", count, disciplina->avaliacoes[i].nome);
                    count++;
                }
            }

            printf("\t\t0 - Sair\n");
            printf("\n\tOpção: ");
            scanf("%d", &op);

            if(op < 0 || op > count)
                printf("RESPOSTA INVÁLIDA!\n\n");

        } while(op < 0 || op > count); //Validação de entrada

        if(op == 0)
            return aluno; //sai

        op--;
        do {
            printf("\n\tInsira a nova nota: ");
            scanf("%f", &busca->nota[op]);
            if (busca->nota[op] < 0 || busca->nota[op] > 10)
                printf("NOTA INVÁLIDA!\n");
        } while (busca->nota[op] < 0 || busca->nota[op] > 10); //Validação de entrada
    } else if (op == 3) {
        if(busca->exame == -1)
            printf("Exame ainda não aplicado\n\n");
        else {
            printf("\n\tInsira a nova nota: ");
            do {
                scanf("%f", &busca->exame);
                if (busca->exame < 0 || busca->exame > 10)
                    printf("NOTA INVÁLIDA!\n");
            } while (busca->exame < 0 || busca->exame > 10);
        }
    }

    return aluno;
}

//Função resposnável por remover um aluno da lista de alunos (retorna um inteiro simulando um booleano: 1 = true, 0 = false)
int removeAluno(Aluno** aluno, char* nome) {
    Aluno *aux = *aluno, *aux2;
    int flag = 1;

    aux = *aluno;
    if (strcmp((*aluno)->nome, nome) == 0) {
        (*aluno) = (*aluno)->prox;
        free(aux);
        flag = 0;
    }
    while (aux->prox) {
        if (strcmp((aux->prox)->nome, nome) == 0) {
            flag = 0;
            aux2 = aux->prox;
            aux->prox = (aux->prox)->prox;
            free(aux2);
            break;
        }
        aux = aux->prox;
    }
    if (flag) {
        printf("ALUNO NÃO ENCONTRADO!\n");
        return 0; //false - não removeu aluno
    }

    return 1; // true - aluno removido
}

//Função responsável por inserir uma nova aula
void cotidiano(Disciplina **disciplina) {

    Disciplina *busca = (*disciplina);
    Aula *aula, *novo = malloc(sizeof(Aula)), *aux, *aux_ant;
    int fim = 1;
    int i = 1, op, validacaoData, ano = (*disciplina)->ano;

    //Bloco responsável por apresentar as disciplinas para o usuário escolher
    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome);
        busca = busca->prox;
        i++;
    }
    printf("\t\t 0 - Voltar\n");
    i--;
    do {
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i); //Validação de entrada

    if(op == 0)
        return;
    
    busca = (*disciplina);
    for(i = 1; i < op; i++)
        busca = busca->prox;

    novo = lerInfoAula(&busca); //Chama função que preenche os campos da struct Aula

    //A seguir ocorre a inserção ordenada da aula de acordo com a data
    if (busca->aulas == NULL) {
        busca->aulas = novo;
        novo->prox = NULL;
    }
    else if (novo->data.dia < busca->aulas->data.dia && novo->data.mes <= busca->aulas->data.mes) {
        novo->prox = busca->aulas;
        busca->aulas = novo;
    }
    else {

        aux = busca->aulas->prox;
        aux_ant = busca->aulas;

        while (aux != NULL) {
            if (novo->data.dia < aux->data.dia  && novo->data.mes <= aux->data.mes) {
                fim = 0;
                novo->prox = aux;
                aux_ant->prox = novo;
            }
            aux_ant = aux;
            aux = aux->prox;
        }
        if(fim) {
            aux_ant->prox = novo;
            novo->prox = NULL;
        }
    }

    //Após a inserção, numeramos as aulas
    i = 1;
    aux = busca->aulas;
    while(aux) {
        aux->numero = i;
        aux = aux->prox;
        i++;
    }
}

//Função responsável por ler as informações de uma aula e preencher a struct Aula
Aula * lerInfoAula(Disciplina **disciplina) {

    Aula *novo = malloc(sizeof(Aula));
    Aluno *busca = (*disciplina)->alunos;
    int ano = (*disciplina)->ano,  validacaoData;
    char charPresenca;
    int i = 0;

    do {
        system(clear);
        printf("\n\tInsira a data (DD MM): ");
        scanf("%d %d", &novo->data.dia, &novo->data.mes);
        novo->data.ano = ano;
        validacaoData = validaData(novo->data.dia, novo->data.mes, novo->data.ano);
        if (validacaoData == 0)
            printf("DATA INVÁLIDA!\n");
    } while (validacaoData == 0); //Validação de entrada

    printf("\tInsira o conteudo da aula: ");
    scanf(" %[^\n]s", novo->conteudo);
    novo->horas = (*disciplina)->horasAula;    
    (*disciplina)->horasRealizadas += novo->horas;

    printf("\tInsira a presença dos alunos('P' - presente / 'F' - Falta): ");
    while (busca) {
        printf("\n\t - %s: ", busca->nome);
        scanf(" %c", &charPresenca);

        if(charPresenca == 'P')
            busca->frequencia++;
        i++;

        busca = busca->prox;
    }

    return novo; //Retorna novo nó da lista de Aulas
}

//Função responsável por remover uma disciplina
Disciplina* removeDisciplina(Professor* prof) {

    Disciplina *antes, *aux = prof->disciplinas;
    int i, id, N = prof->quantidadeDisciplinas;
    char *nomeArquivo = malloc(sizeof(char)*51);

    system(clear);
    printf("\t\tInsira o número da disciplina a ser removida:\n");

    //Apresenta todas as disciplinas 
    for (i=0; i<N; i++) {
        printf("\t%d - %s\n", i+1, aux->nome);
        aux = aux->prox;
    }

    printf("\t0 - Voltar");
    do {
        printf("\n\n\tOpção: ");
        scanf("%d", &id);
        if (id < 0 || id > N)
            printf("OPÇÃO INVÁLIDA!\n");
    } while (id < 0 || id > N); //Validação de entrada
    id--;

    if(id == -1)
        return prof->disciplinas; //Volta

    aux = antes = prof->disciplinas;
    if (id == 0) {

        aux = aux->prox; //remove o primeiro elemento da lista / primeira disciplina
        return aux;
    }
    else {
        while (id > 0) {
            antes = aux;
            aux = aux->prox;
            id--;
        }
        antes->prox = aux->prox;
    }
    prof->quantidadeDisciplinas--; //diminui a quantidade de disciplinas na struct professor
    return antes;
}

//Função responsável por inserir notas de uma disciplna
Professor* addNotas(Professor* prof) {

    Disciplina *busca = prof->disciplinas;
    Aluno *aluno;
    int i = 1, op, count;

    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome);
        busca = busca->prox;
        i++;
    }
    i--;
    printf("\t\t 0 - Voltar");

    do {
        printf("\n\tOpção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i); //Validação de entrada

    if(op == 0)
        return prof; //sair

    busca = prof->disciplinas;
    for(i = 1; i < op; i++)
        busca = busca->prox;

    if(busca->provas > 0 || busca->trabalhos > 0) { //Só é possivel adicionar notas caso a disciplina tenha alguma disciplina cadstrada
        count = 1;
        i = 0;
        system(clear);
        printf("\n\n\t\tSelecione a avaliação:\n");
        while (i < 14) {
            if(busca->avaliacoes[i].tipo != 'N') {
                printf("\t\t %d - %s\n", count, busca->avaliacoes[i].nome);
                count++;
            }   
            i++;
        }
        printf("\t\t 0 - Voltar");
        
        count--;
        do {
            printf("\n\tOpção: ");
            scanf("%d", &op);
            if(op < 0 || op > count)
                printf("RESPOSTA INVÁLIDA!\n\n");
        } while (op < 0 || op > count); //Validação de entrada

        

        if(op == 0)
            return prof; //sair

        aluno = busca->alunos;
        i = 0;
        op--;
        while (op > 0) {
            if(busca->avaliacoes[i].tipo != 'N') {
                op--;
            }
            i++;
        }
        system(clear);
        printf("Insira a nota dos alunos:\n");

        //Passa de aluno em aluno preenchendo a nota da avaliação selecionada
        while(aluno) {
            do {
                printf("- %s: ", aluno->nome);
                scanf("%f", &aluno->nota[i]);
                if(aluno->nota[i]< 0 || aluno->nota[i] > 10)
                    printf("NOTA INVÁLIDA\n");
            } while(aluno->nota[i]< 0 || aluno->nota[i] > 10);
            aluno = aluno->prox;
        }
    }
    
    return prof;
}

//Função responsável por inserir a nota dos alunos que ficaram de exame
Professor* recuperacao(Professor *prof) {

    Disciplina *busca = prof->disciplinas;
    Aluno *aluno;
    int i = 1, op, count;

    //Busca a disciplina
    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome);
        busca = busca->prox;
        i++;
    }
    printf("\t\t 0 - Voltar");
    i--;

    do {
        printf("\n\n\tOpção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i);

    if(op == 0)
        return prof; //sair
    
    busca = prof->disciplinas;
    for(i = 1; i < op; i++)
        busca = busca->prox;

    aluno = busca->alunos;
    //passa de aluno em aluno preechendo nota do exame
    system(clear);
    printf("Insira a nota dos alunos:\n");
    while(aluno) {
        if(calculaMedia(aluno, busca) < busca->notaMinima) { //Só apresenta os alunos que estão de exame
            do {
                printf("- %s: ", aluno->nome);
                scanf("%f", &aluno->exame);
                if(aluno->exame < 0 || aluno->exame > 10)
                    printf("NOTA INVÁLIDA\n");
            } while(aluno->exame < 0 || aluno->exame > 10);
        }
        aluno = aluno->prox;
    }

    return prof;    
}

//Função responsável por encerrar o semestre e apresentar a situação de cada aluno
void fecharSemestre (Disciplina *disciplinas) {
    Disciplina *aux = disciplinas;
    Aluno *aluno;
    int i = 1, op;
    float media, freq;
    char c;

    //Busca disciplina
    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (aux) {
        printf("\t\t %d - %s\n", i, aux->nome);
        aux = aux->prox;
        i++;
    }
    printf("\t\t 0 - Voltar");
    i--;
    do {
        printf("\n\t\t Opção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i); //Validação de entrada

    if(op == 0)
        return;
    
    aux = disciplinas;
    for(i = 1; i < op; i++)
        aux = aux->prox;

    system(clear);
    if (aux->horasRealizadas < aux->horasPrevistas) {
        printf("Horas realizadas menor que as horas previstas. Tem certeza que deseja continuar?\n\t1- Sim\n\t2- Nao");
        do {
            scanf("%d", &op);
            if (op < 1 || op > 2)
                printf("OPÇÃO INVÁLIDA!\n");
        } while (op < 1 || op > 2); //Validação de entrada
        if (op == 2)
            return;
    }
    aluno = aux->alunos;

    flush_in();

    //Passa de aluno em aluno apresentando sua média, frequência e a situação final
    while (aluno) {
        media = calculaMedia(aluno, aux);
        freq = calculaFrequencia(aluno, aux);
        printf("%s:\n\tMédia: %.2f\n\tFrequência: %.2f%%\n\tSituação: ", aluno->nome, media, freq);
        if (freq < aux->frequenciaMinima)
            printf("Reprovado por falta.");
        else if (media < aux->notaMinima)
            printf("Reprovado.");
        else
            printf("Aprovado.");
        printf("\n\n\tPressione ENTER para seguir.\n");
        getchar();
        aluno = aluno->prox; 
    }
}

// Função responsável por imprimir o relatório dos alunos de uma disciplina 
void relatorioAlunos(Disciplina *disciplina) {
   
    Aluno *aluno;
    int op, i = 1, flag = 1;
    float media, freq;

    aluno = disciplina->alunos;

    char nomeArquivo[100] = "Relatorio Aluno ";
    strcat(nomeArquivo, disciplina->nome);
    strcat(nomeArquivo, ".txt");
    ajustaStr(nomeArquivo);
    ajustaStr2(nomeArquivo);

    FILE *fp = fopen(nomeArquivo, "w"); //Abre um arquivo onde iremos imprimir o relatório

    system(clear);
    printf("-------------------------------------------------------------------------------");
    printf("\n\n\t\tRELATÓRIO DOS ALUNOS NA DISCIPLINA %s:\n", disciplina->nome);
    fprintf(fp, "\t\tRELATÓRIO DOS ALUNOS NA DISCIPLINA %s:\n", disciplina->nome);

    aluno = disciplina->alunos;

    //passa por todos os alunos imprimindo o relatório
    while (aluno) {
        printf("\n------------------------------------------------------");
        printf("\nNome: %s", aluno->nome);
        printf("\nNúmero: %d", aluno->numero);
        printf("\n\nAVALIAÇÕES: ");
        fprintf(fp, "\n------------------------------------------------------");
        fprintf(fp, "\nNome: %s", aluno->nome);
        fprintf(fp, "\nNúmero: %d", aluno->numero);
        fprintf(fp, "\n\nAVALIAÇÕES: ");
        for (i = 0; i < 14; i ++) {
            if(disciplina->avaliacoes[i].tipo != 'N' && aluno->nota[i] != -1) {
                printf("\nNome da avaliação: %s", disciplina->avaliacoes[i].nome);
                fprintf(fp, "\nNome da avaliação: %s", disciplina->avaliacoes[i].nome);

                printf("\nTipo da avaliação: %c", disciplina->avaliacoes[i].tipo);
                fprintf(fp, "\nTipo da avaliação: %c", disciplina->avaliacoes[i].tipo);

                printf("\nNota do aluno: %.2f\n", aluno->nota[i]);
                fprintf(fp, "\nNota do aluno: %.2f\n", aluno->nota[i]);
                flag = 0;
            }                
        }
        if(aluno->exame != -1)
            printf("\nNota do exame: %.2f\n", aluno->exame);
            fprintf(fp, "\nNota do exame: %.2f\n", aluno->exame);

        media = calculaMedia(aluno, disciplina);
        freq = calculaFrequencia(aluno, disciplina);
        printf("\nPresença: %d/%d", aluno->frequencia, disciplina->aulasPrevistas);
        fprintf(fp, "\nPresença: %d/%d", aluno->frequencia, disciplina->aulasPrevistas);

        printf("\nFrequência: %.2f%%", freq);
        fprintf(fp, "\nFrequência: %.2f%%", freq);

        if (!flag) {
            printf("\n\nMédia final: %.2f", media);
            fprintf(fp, "\n\nMédia final: %.2f", media);
        }
        else {
            printf("\n\nNão é possivel calcular a média.");
            fprintf(fp, "\n\nNão é possivel calcular a média.");
        }
            
        printf("\nSituação: ");
        fprintf(fp, "\nSituação: ");
        if(disciplina->horasPrevistas > disciplina->horasRealizadas) {
            printf("Cursando.");
            fprintf(fp, "Cursando.");
        }
        else if (freq < disciplina->frequenciaMinima) {
            printf("Reprovado por falta.");
            fprintf(fp, "Reprovado por falta.");
        }
        else if (media < disciplina->notaMinima) {
            printf("Reprovado por nota.");
            fprintf(fp, "Reprovado por nota.");
        }
        else {
            printf("Aprovado.");
            fprintf(fp, "Aprovado.");
        }
            
                    
        printf("\n");
        fprintf(fp, "\n");
        aluno = aluno->prox;
        printf("\n\n\tPressione ENTER para seguir.\n");
        getchar();
        system(clear);
    }

    fclose(fp); //Fecha e salva o arquivo relatório
    free(fp);
}

//Função responsável por escolher uma disciplina para chamar uma outra função que imprime o relatório
void relatorioTurmaEspecifica(Professor *prof) {
    Disciplina *busca = prof->disciplinas;
    Aluno *aluno;
    int op, i = 1;

    system(clear);
    printf("\n\n\t\tSelecione a disciplina para ter o relatório:\n");
    while (busca != NULL) {
        printf("\t\t%d - %s\n", i, busca->nome);
        busca = busca->prox;
        i ++;
    }
    printf("\t\t0 - Voltar");
    i --;
    do {
        printf("\n\n\tOpção: ");
        scanf(" %d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i);

    if(op == 0)
        return;
    
    flush_in();
    busca = prof->disciplinas;
    for (i = 1; i < op; i ++)
        busca = busca->prox;
    relatorioAlunos(busca);

}

//Função responsável por imprimir relatório das notas de todas as turmas 
void relatorioNotas (Professor  *prof) {

    Disciplina *disciplina = prof->disciplinas;
    Aluno *aluno = disciplina->alunos;
    FILE * fp;

    int i;
    float notaMin = 10, notaMax = 0, media, somaMediaTurma = 0;
    char nomeArquivo[130];
    
    system(clear);
    while (disciplina) {

        strcpy(nomeArquivo, "Relatorio Nota ");
        strcat(nomeArquivo, disciplina->nome);
        ajustaStr(nomeArquivo);
        ajustaStr2(nomeArquivo);
        strcat(nomeArquivo, ".txt");
        fp = fopen(nomeArquivo, "w");

        printf("-------------------------------------------------------------------------------");
        printf("\n\t\tRELATÓRIO DAS NOTAS DA DISCIPLINA %s\n", disciplina->nome);
        fprintf(fp, "\t\tRELATÓRIO DAS NOTAS DA DISCIPLINA %s\n", disciplina->nome);

        notaMin = 10;
        somaMediaTurma = 0;
        notaMax = 0;
        aluno = disciplina->alunos;

        printf("\n\nNome da disciplina: %s", disciplina->nome);
        printf("\nCódigo da disciplina: %s", disciplina->codigo);
        fprintf(fp, "\nNome da disciplina: %s", disciplina->nome);
        fprintf(fp, "\nCódigo da disciplina: %s", disciplina->codigo);

        while (aluno) {
            media = calculaMedia(aluno, disciplina);
            if (media > notaMax) {
                notaMax = media;
            }
            if (media < notaMin) {
                notaMin = media;
            }
            somaMediaTurma += media;
            aluno = aluno->prox;
        }
        if(notaMin == -1) {
            printf("\nNão foi aplicada nenhuma avaliação nesta turma");
            fprintf(fp, "\nNão foi aplicada nenhuma avaliação nesta turma");
        }
        else {
            printf("\nA maior nota da turma é: %.2f", notaMax);
            printf("\nA menor nota da turma é: %.2f", notaMin);
            printf("\nA média da turma é: %.2f", somaMediaTurma/disciplina->quantidadeAlunos);
            fprintf(fp, "\nA maior nota da turma é: %.2f", notaMax);
            fprintf(fp, "\nA menor nota da turma é: %.2f", notaMin);
            fprintf(fp, "\nA média da turma é: %.2f", somaMediaTurma/disciplina->quantidadeAlunos);
        }
        disciplina = disciplina->prox;

        fclose(fp);
        free(fp);

        flush_in();
        printf("\n\n\tPressione ENTER para seguir.\n");
        getchar();
        system(clear);
    }
}

//Função respomsável por imprimir relatório da situação de todos os alunos de uma turma
void relatorioAprovacao (Professor *prof) {
    Disciplina *busca = prof->disciplinas;
    Aluno *aluno;
    float media, freq;
    int op, i = 1;
    char nomeArquivo[100] = "Relatorio Aprovacao ";

    system(clear);
    printf("\n\n\t\tSelecione a disciplina:\n");
    while (busca) {
        printf("\t\t %d - %s\n", i, busca->nome);
        busca = busca->prox;
        i++;
    }
    printf("\t\t 0 - Voltar");
    i--;
    do {
        printf("\n\n\tOpção: ");
        scanf("%d", &op);
        if(op < 0 || op > i)
            printf("RESPOSTA INVÁLIDA!\n\n");
    } while (op < 0 || op > i);

    if(op == 0)
        return;
    
    busca = prof->disciplinas;
    for(i = 1; i < op; i++)
        busca = busca->prox;

    strcat(nomeArquivo, busca->nome);
    strcat(nomeArquivo, ".txt");
    ajustaStr(nomeArquivo);
    ajustaStr2(nomeArquivo);

    FILE *fp = fopen(nomeArquivo, "w"); //Abre o arquivo pra impressão do relatório da disciplina selecionada

    system(clear);
    printf("\n\n\t\tRELATÓRIO DE APROVAÇÃO DA DISCIPLINA %s:", busca->nome);
    fprintf(fp, "\t\tRELATÓRIO DE APROVAÇÃO DA DISCIPLINA %s:", busca->nome);

    aluno = busca->alunos;
    flush_in();
     while (aluno) {

        media = calculaMedia(aluno, busca);
        freq = calculaFrequencia(aluno, busca);

        printf("\n\n%s:\n\tMédia: %.2f\n\tFrequência: %.2f%%\n\tSituação: ", aluno->nome, media, freq);
        fprintf(fp, "\n\n%s:\n\tMédia: %.2f\n\tFrequência: %.2f%%\n\tSituação: ", aluno->nome, media, freq);

        if (freq < busca->frequenciaMinima) {
            printf("Reprovado por falta.");
            fprintf(fp, "Reprovado por falta.");
        } else if (media < busca->notaMinima) {
            printf("Reprovado.");
            fprintf(fp, "Reprovado.");
        } else {
            printf("Aprovado.");
            fprintf(fp, "Aprovado.");
        }
        printf("\n\n\tPressione ENTER para seguir.\n");
        getchar();
        aluno = aluno->prox;
    }

    fclose(fp); //Fecha e salva o arquivo
    free(fp);
}

//Função responsável por apresentar os alunos de exame de uma matéria específica
void relatorioExame(Disciplina *disciplina) {

    Aluno *aluno = disciplina->alunos;

    int flag = 1;
    float media;
    char nomeArquivo[100] = "Relatorio Exame ";

    strcat(nomeArquivo, disciplina->nome);
    strcat(nomeArquivo, ".txt");
    ajustaStr(nomeArquivo);
    ajustaStr2(nomeArquivo);

    FILE *fp = fopen(nomeArquivo, "w");

    system(clear);
    printf("\n\n-------------------------------------------------------------------------------");
    printf("\n\n\t\tRELATÓRIO DOS ALUNOS DE EXAME NA DISCIPLINA %s:\n", disciplina->nome);
    fprintf(fp, "\t\tRELATÓRIO DOS ALUNOS DE EXAME NA DISCIPLINA %s:\n", disciplina->nome);    

    while (aluno) {
        media = calculaMedia(aluno, disciplina);
        if(media < disciplina->notaMinima && media != -1){
            printf("\t- %s media: %.2f ---- Nota necessária: %.2f\n", aluno->nome, media, ((disciplina->notaMinima*2)-media));
            fprintf(fp, "- %s media: %.2f ---- Nota necessária: %.2f\n", aluno->nome, media, ((disciplina->notaMinima*2)-media));
            flag = 0;
        }
        aluno = aluno->prox;
    }

    if(flag) {
        printf("NÃO FOI APLICADO AVALIAÇÕES NESTA TURMA\n");
        fprintf(fp, "NÃO FOI APLICADO AVALIAÇÕES NESTA TURMA\n");        
    }

    fclose(fp); //Fecha e salva o arquivo
    free(fp);

    printf("\n\n\tPressione ENTER para seguir.\n");
    getchar();

}