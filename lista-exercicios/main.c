/**
Dada uma tabela de espalhamento (Hashing Table), resultante da inserção de
registros com as chaves A, N, L, U, C, I, R, S, T, M, E, O (com cada letra
correspondendo a sua posição no alfabeto, ex: A = 1, B = 2, C = 3, ...) nesta
ordem, numa tabela inicialmente vazia de tamanho 7 e, sabendo-se que a função
de espalhamento é h(k) = (k2 + k –1) mod 7 (mod é o resto da divisão), para a k-
ésima letra do alfabeto e que as colisões foram tratadas com listas encadeadas,
indique quantas comparações seriam necessárias para encontrar os elementos
E, T, I e M numa busca nesta tabela. Explique como você chegou a esses
valores, mostrando a tabela construída.
**/

#include <stdio.h>
#include <stdlib.h>

#define TAM 7

// lista encadeada
typedef struct no{
    int chave;
    struct no *proximo;
}No;

typedef struct {
    No *inicio;
    int tam;
}Lista;

void iniciarLista(Lista *l){
    l->inicio = NULL;
    l->tam = 0;
}

void inserirNaLista(Lista *l, int valor){
    No *novo = malloc(sizeof(No));
    if (novo){
        novo->chave = valor;
        novo->proximo = l->inicio;
        l->inicio = novo;
        l->tam++;
    }else{
        printf("\nErro ao alocar memoria");
    }
}

int buscarNaLista(Lista *l, int chave){
    No *aux = l->inicio;
    while (aux->proximo != NULL && aux->chave != chave)
        aux = aux->proximo;
    if (aux != NULL && aux->chave == chave)
        return aux->chave;
    return 0;
}

void imprimirLista(Lista *l){
    No *aux = l->inicio;
    printf("Tam: %d \t", l->tam);
    while (aux != NULL){
        printf("%d -> ", aux->chave);
        aux = aux->proximo;
    }
}

// hash table
void inicializarTabela(Lista t[]){
    int i;
    for (i=0; i<TAM; i++)
        iniciarLista(&t[i]);
}

int funcaoHash(int chave){
    //h(k) = (k2 + k –1) mod 7
    return (chave*chave + chave - 1) % TAM;
    //return chave % TAM;
}

void inserirNaTabela(Lista t[], int chave){
    int id = funcaoHash(chave);
    inserirNaLista(&t[id], chave);
}

int buscarNaTabela(Lista t[], int chave){
    int id = funcaoHash(chave);
    return buscarNaLista(&t[id], chave);
}

void imprimirTabela(Lista t[]){
    int i;
    for (i = 0; i < TAM; i++) {
        printf("%2d = ", i);
        imprimirLista(&t[i]);
        printf("\n");
    }
}


int main() {
    Lista tabela[TAM];
    inicializarTabela(tabela);

    int opcao, chave;

    do {
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                inserirNaTabela(tabela, chave);
                break;
            case 2:
                printf("Digite a chave: ");
                scanf("%d", &chave);
                if (buscarNaTabela(tabela, chave))
                    printf("Chave encontrada");
                else
                    printf("Chave nao encontrada");
                break;
            case 3:
                imprimirTabela(tabela);
                break;
            default:
                break;
        }

    } while (opcao != 0);

    return 0;
}
