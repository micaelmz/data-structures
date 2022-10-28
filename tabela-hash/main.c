#include <stdio.h>
#include <stdlib.h>

#define TAM 31

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
    return chave % TAM;
}

void inserir(Lista t[], int valor){
    int id = funcaoHash(valor);
    inserirNaLista(&t[id], valor);
}

int buscar(Lista t[], int chave){
    int id = funcaoHash(chave);
    printf("\n\tIndice gerado: %d\n", id);
    return buscarNaLista(&t[id], chave);
}

void imprimir(Lista t[]){
    int i;
    for (i = 0; i < TAM; i++) {
        printf("%2d = ", i);
        imprimirLista(&t[i]);
        printf("\n");
    }
}

int main() {

    int opcao, valor, retorno;
    Lista tabela[TAM];

    inicializarTabela(tabela);

    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                printf("\tQual valor quer inserir\n");
                scanf("%d", &valor);
                inserir(tabela, valor);
                break;
            case 2:
                printf("\tQual valor quer buscar\n");
                scanf("%d", &valor);
                retorno = buscar(tabela, valor);
                if (retorno != 0)
                    printf("\tValor encontrado: %d", retorno);
                else
                    printf("\tvalor n encontrado");
                break;
            case 3:
                imprimir(tabela);
                break;
            case 4:
                break;
            default:
                printf("opcao invalida");
        }
    }while(opcao != 0);
    return 0;
}
