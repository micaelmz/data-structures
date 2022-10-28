#include <stdio.h>
#include <string.h>

#define STRING_S 50
#define TAMANHO 11 // maximo 6 pessoas

typedef struct {
    char rua[STRING_S];
    char bairro[STRING_S];
    int numero;
    long cep;
}Endereco;

typedef struct {
    char cargo[STRING_S];
    char empresa[STRING_S];
    int carga_horaria;
    float salario;
}Profissao;

typedef struct{
    char nome[STRING_S];
    int idade;
    long cpf;
    int mes, ano, dia; // data de nascimento
    Endereco endereco;
    Profissao profissao;
}Pessoa;


void inicializarPessoas(Pessoa lista[]){
    int i;
    for (i = 0; i < TAMANHO; i++){
        strcpy(lista[i].nome,"");
    }
}

void imprimirLista(Pessoa lista[]){
    int i, tamanho;
    for (i = 0; i < TAMANHO; i++){
        printf("\n%2d", i+1);
        tamanho = strlen(lista[i].nome);
        if (tamanho > 0){
            printf("\n\t%s", lista[i].nome);
            printf("\nIdade: %d", lista[i].idade);
            printf("\nCPF: %l", lista[i].cpf);
            printf("\nData de Nascimento: %d/%2d/%4d", lista[i].dia, lista[i].mes, lista[i].ano);
            printf("\nEndereco:");
            printf("\n\tRua: %s", lista[i].endereco.rua);
            printf("\n\tBairro: %s", lista[i].endereco.bairro);
            printf("\n\tN. %d", lista[i].endereco.numero);
            printf("\n\tCEP: %l", lista[i].endereco.cep);
            printf("\nProfissao:");
            printf("\n\tEmpresa: %s", lista[i].profissao.empresa);
            printf("\n\tCargo: %s", lista[i].profissao.cargo);
            printf("\n\tCarga Horaria: %d", lista[i].profissao.carga_horaria);
            printf("\n\tSalario: R$%.2f", lista[i].profissao.salario);
        }
        printf("\n==========================");
    }
}

int funcaoHash(char nome[50]){
    int tamanho_nome = strlen(nome);
    int i, contagem = 0;

    for (i = 0; i < tamanho_nome; i++){
        contagem += nome[i] * i;
    }
    return contagem % TAMANHO;
}

void cadastrarPessoa(Pessoa lista[]){

    while ()
}

int main() {
    Pessoa lista[TAMANHO];

    inicializarPessoas(lista);

    int opcao;

    do{
        printf("\n\tBem vindo ao cadastro de pessoas!\n\tEscolha uma opcao: \n");
        printf("\t0 - Sair\n\t1 - Imprimir Lista\n\t2 - Cadastrar Pessoa\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimirLista(lista);
                break;
            case 2:
                formulaHash("Micaell");
                break;
            default:
                printf("\nOpcao invalida!");
        }

    } while (opcao != 0);

    printf("Hello, World!\n");
    return 0;
}
