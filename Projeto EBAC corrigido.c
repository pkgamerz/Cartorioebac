#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/* ---------------------------------------------
   CORES ANSI
--------------------------------------------- */
#define RESET    "\033[0m"
#define CIANO    "\033[1;36m"
#define AMARELO  "\033[1;33m"
#define VERDE    "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define BRANCO   "\033[1;37m"
#define CINZA    "\033[0;90m"

/* Limpa o buffer do teclado apos scanf */
#define LIMPAR_BUFFER() { int _c; while((_c = getchar()) != '\n' && _c != EOF); }

/* ---------------------------------------------
   REGISTRO
--------------------------------------------- */
int registro()
{
    char arquivo[40];
    char cpf[40];
    char nome[40];
    char sobrenome[40];
    char cargo[40];

    printf("\n" CIANO "  +------------------------------------------+" RESET "\n");
    printf(     CIANO "  |        SISTEMA DE CADASTRO DE DADOS       |" RESET "\n");
    printf(     CIANO "  +------------------------------------------+" RESET "\n\n");

    printf("  " CINZA "CPF       : " RESET); scanf("%s", cpf);       LIMPAR_BUFFER();
    printf("  " CINZA "Nome      : " RESET); scanf("%s", nome);      LIMPAR_BUFFER();
    printf("  " CINZA "Sobrenome : " RESET); scanf("%s", sobrenome); LIMPAR_BUFFER();
    printf("  " CINZA "Cargo     : " RESET); scanf("%s", cargo);     LIMPAR_BUFFER();

    /* Usa o CPF como nome do arquivo */
    strcpy(arquivo, cpf);

    /* Abre uma unica vez em modo escrita e salva tudo */
    FILE *file = fopen(arquivo, "w");
    if (file == NULL)
    {
        printf("\n" VERMELHO "  [ERRO] Nao foi possivel criar o arquivo.\n" RESET "\n");
        system("pause");
        return 1;
    }

    fprintf(file, "%s,%s,%s,%s", cpf, nome, sobrenome, cargo);
    fclose(file);

    printf("\n" VERDE "  Cadastro realizado com sucesso!" RESET "\n\n");
    system("pause");
    return 0;
}

/* ---------------------------------------------
   CONSULTA
--------------------------------------------- */
int consulta()
{
    char cpf[40];
    char conteudo[200];
    char campo_cpf[40]       = "";
    char campo_nome[40]      = "";
    char campo_sobrenome[40] = "";
    char campo_cargo[40]     = "";

    printf("\n" CIANO "  +------------------------------------------+" RESET "\n");
    printf(     CIANO "  |        SISTEMA DE CONSULTA DE DADOS       |" RESET "\n");
    printf(     CIANO "  +------------------------------------------+" RESET "\n\n");

    printf("  Digite o CPF a ser consultado: ");
    scanf("%s", cpf);
    LIMPAR_BUFFER();

    FILE *file = fopen(cpf, "r");

    if (file == NULL)
    {
        printf("\n" VERMELHO "  [ERRO] CPF nao encontrado no sistema." RESET "\n\n");
        system("pause");
        return 1;
    }

    /* Le e separa os campos por virgula */
    if (fgets(conteudo, 200, file) != NULL)
    {
        char *token = strtok(conteudo, ",");
        if (token) strcpy(campo_cpf,       token);
        token = strtok(NULL, ",");
        if (token) strcpy(campo_nome,      token);
        token = strtok(NULL, ",");
        if (token) strcpy(campo_sobrenome, token);
        token = strtok(NULL, ",\n");
        if (token) strcpy(campo_cargo,     token);
    }

    fclose(file);

    /* Exibe os dados formatados */
    printf("\n" AMARELO "  +----------------------------------------+" RESET "\n");
    printf(     AMARELO "  |      INFORMACOES DO FUNCIONARIO         |" RESET "\n");
    printf(     AMARELO "  +----------------------------------------+" RESET "\n\n");

    printf("  " CINZA "CPF       : " RESET BRANCO "%s" RESET "\n", campo_cpf);
    printf("  " CINZA "Nome      : " RESET BRANCO "%s" RESET "\n", campo_nome);
    printf("  " CINZA "Sobrenome : " RESET BRANCO "%s" RESET "\n", campo_sobrenome);
    printf("  " CINZA "Cargo     : " RESET BRANCO "%s" RESET "\n", campo_cargo);

    printf("\n" CIANO "  ----------------------------------------" RESET "\n");
    printf(VERDE "\n  Consulta realizada com sucesso!" RESET "\n\n");

    system("pause");
    return 0;
}

/* ---------------------------------------------
   DELETAR
--------------------------------------------- */
int deletar()
{
    char cpf[40];

    printf("\n" VERMELHO "  +------------------------------------------+" RESET "\n");
    printf(     VERMELHO "  |          SISTEMA DE EXCLUSAO DE DADOS     |" RESET "\n");
    printf(     VERMELHO "  +------------------------------------------+" RESET "\n\n");

    printf("  Digite o CPF a ser deletado: ");
    scanf("%s", cpf);
    LIMPAR_BUFFER();

    if (remove(cpf) == 0)
        printf("\n" VERDE "  Registro deletado com sucesso!" RESET "\n\n");
    else
        printf("\n" VERMELHO "  [ERRO] CPF nao encontrado no sistema." RESET "\n\n");

    system("pause");
    return 0;
}

/* ---------------------------------------------
   MAIN
--------------------------------------------- */
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao = 0;

    while (1)
    {
        system("cls");

        printf("\n" CIANO "  +==========================================+" RESET "\n");
        printf(     CIANO "  |          CARTORIO DA EBAC                |" RESET "\n");
        printf(     CIANO "  +==========================================+" RESET "\n\n");

        printf("  Escolha a opcao desejada:\n\n");
        printf("  " AMARELO "[1]" RESET " Registrar funcionario\n");
        printf("  " AMARELO "[2]" RESET " Consultar funcionario\n");
        printf("  " AMARELO "[3]" RESET " Deletar funcionario\n");
        printf("  " VERMELHO "[0]" RESET " Sair\n");

        printf("\n" CINZA "  Opcao: " RESET);
        printf("\n\n\n" CINZA"  Projeto de Patrick H Kamimura ");
        scanf("%d", &opcao);
        LIMPAR_BUFFER();

        system("cls");

        switch (opcao)
        {
            case 1: registro(); break;
            case 2: consulta(); break;
            case 3: deletar();  break;
            case 0:
                printf("\n" VERDE "  Encerrando o sistema. Ate logo!" RESET "\n\n");
                return 0;
            default:
                printf("\n" VERMELHO "  [AVISO] Opcao invalida. Tente novamente." RESET "\n\n");
                system("pause");
                break;
        }
    }
}
