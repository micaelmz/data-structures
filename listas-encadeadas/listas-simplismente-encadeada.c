
#include <stdlib.h>
#include <stdio.h>


//typedef struct node{
//    int value;
//    struct node *next;
//}Node;

// LISTA DUPLAMENTE ENCADEADA
typedef struct node{
    int value;
    struct node *next, *prev;
}Node;

// LISTA CIRCULAR
//typedef struct node{
//    int value;
//    struct node *next;
//}Node;


void insert_at_start(Node **list, int num);
void insert_at_end(Node **list, int num);
void insert_in_middle(Node **list, int num, int target);
void print_list(Node *list);
Node* remove_node(Node **list, int value);
void insert_in_order(Node **list, int num);
int sum_of_evens(Node **list);
void unchain_last_node(Node **list);
int get_pos(Node **list, int value);
void merge_list(Node **l1, Node **l2);
void reverse_list(Node **list);
void merge_sorted_list(Node **l1, Node **l2);
void remover_pares(Node **lista, Node **pilha);
void desempilhar(Node **pilha);




int main(){
    int option, value, target;
    Node *deleted_node, *list, *pilha = NULL;

    do{
        printf("\n\t0 - Sair\n\t1 - Imprimir Lista\n\t2 - Inserir no inicio\n\t3 - Inserir no fim\n\t4 - Inserir no meio\n\t5 - Remover\n\t6 - Remover pares\n\t7 - Desempilhar");
        scanf("%d", &option);

        switch (option) {
            case (1):
                print_list(list);
                break;
            case (2):
                printf("\nDigite um valor: \n");
                scanf("%d", &value);
                insert_at_start(&list, value);
                break;
            case (3):
                printf("\nDigite um valor: \n");
                scanf("%d", &value);
                insert_at_end(&list, value);
                break;
            case (4):
                printf("\nDigite um valor e o local a ser inserido: \n");
                scanf("%d%d", &value, &target);
                insert_in_middle(&list, value, target);
                break;
            case (5):
                printf("\nDigite o valor a ser removido: \n");
                scanf("%d", &value);
                // tirei ele da lista porém ainda existe no programa e na memoria, basicamente so quebrei o elo da corrente
                deleted_node = remove_node(&list, value);
                // ai aqui eu deleto e libero a memoria dele, que tava por ai flutuando
                free(deleted_node);
                break;
            case (6):
                remover_pares(&list, &pilha);
                break;
            case (7):
                desempilhar(&pilha);
                break;
            default:
                if (option != 0){
                    printf("Opção Invalida!");
                }
        }
    } while (option != 0);

    return 0;
}


void insert_at_start(Node **list, int num){
    // cria um novo node pra fazer parte da lista
    Node *new_node = malloc(sizeof(Node));

    // se tiver criado com sucesso
    if (new_node){
        // o valor é o valor e o que vem dps desse node, é a lista inteira, já que ele ta antes da lista, ou seja, no inicio
        // ele ta movendo toda lista pra depois dele
        new_node->value = num;
        new_node->next = *list;
        // agr o inicio da lista, no caso o ponteiro pra list, é o proprio novo node, pq ele é o inicio
        *list = new_node;
    }else
        // se n conseguir criar, da erro
        printf("Erro ao alocar memoria");
}

void insert_at_end(Node **list, int num){
    Node *aux, *new_node = malloc(sizeof(Node));
    // cria um novo node pra fazer parte da lista
    if (new_node){
        // o valor é o valor e como é o ultimo elemento, o proximo é ninguem, ou seja, NULL
        new_node->value = num;
        new_node->next = NULL;

        // se a lista tiver vazia, então a lista so vai ter um node, que é exatamente o new_node, que acabou de ser criado
        if (*list == NULL){
            *list = new_node;
        }
            // se n tiver vazia, ele cria um auxiliar pra lista, como se fosse um backup dela, que nada mais é que o primeiro
            // elemento da lista, e esse elemento vai passano por todos itens até achar o null, ou seja, o final
            // apos encontrar o final, ele passa a apontar pro node que acabou de criar, ou seja, dps de toda lista vem esse node
            // justamente pq ele ta no final
        else{
            aux = *list;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = new_node;
        }
        // se n conseguir alocar da erro
    }else{
        printf("Erro ao alocar memoria");
    }
}

void insert_in_middle(Node **list, int num, int target){
    // cria um novo node pra fazer parte da lista
    Node *aux, *new_node = malloc(sizeof(Node));

    // se a alocação tiver funcionado, tudo certo (isso é boa pratica)
    if (new_node){
        // como padrão, o valor do node é o valor que o usuario quer que seja e passou
        new_node->value = num;

        // se a lista tiver vazia, a lista então é o proprio node solitario, sendo seu proximo null (como sempre em fim de lista)
        if (*list == NULL){
            new_node->next = NULL;
            *list = new_node;
        }
            // se a lista n tiver vazia, ele cria um auxiliar pra percorrer a lista, enquanto a lista fica la parada
            // apotando qual o inicio, ja que ele n pode sair dali
        else{
            aux = *list;
            // enquanto n chegar no target que o usuario que inserir dps dele, ou até n chegar no final da lista (caso
            // o valor passado n exista na lista, ele continua procurando
            while (aux->value != target && aux->next != NULL) {
                aux = aux->next;
            }
            // achou, o aux travou justamente no local que tem aquele valor, ele ta segurando aquele node no seu conteudo
            // então o proximo elemento do nosso node, é o antigo proximo do aux, já que agr oq vem apos o aux, ou seja
            // aquele elemento indicado pelo usuario, é justamente o valor que enfiamos ali, ou seja, nosso node
            new_node->next = aux->next;
            // apos isso, o node auxiliar agr aponta pra o nosso node, pq justamente o nosso node vem apos o valor indicado
            aux->next = new_node;
        }
    }
    else{
        printf("Erro ao alocar memoria");
    }
}

void insert_in_order(Node **list, int num){
    Node *aux, *new_node = malloc(sizeof(Node));

    if (new_node){
        new_node->value = num;

        if (*list == NULL){
            new_node->next = NULL;
            *list = new_node;
        }
        else{
            aux = *list;
            while (aux->value < num && aux->next != NULL) {
                aux = aux->next;
            }
            new_node->next = aux->next;
            aux->next = new_node;
        }
    }
    else{
        printf("Erro ao alocar memoria");
    }
}

void print_list(Node *list){
    printf("\n\tLista: \n");
    while (list != NULL){
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n\n");
}

Node* remove_node(Node **list, int value){
    // faz duas coisas, tira da corrente o elo desejado, e retorna um ponteiro para ele, para depois ele ser limpo da memoria
    Node *aux, *remove = NULL;

    // se for uma lista vazia
    if (list != NULL){
        // list aponta sempre pro primeiro elemento, usando (*list) ta pegando
        // o node do primeiro elemento, ou seja, qual valor e next do primeiro elemento a lista
        if ((*list)->value == value){
            // ai no caso vai remover não a lista, mas o primeiro elemento da lista, pq o ponteiro da
            // lista sempre aponta pro primeiro elemento da lista
            remove = *list;
            // a lista agora na verdade começa no segundo elemento
            *list = (*list)->next;
        }
        else{
            aux = *list;
            // o elemento pode não existir na lista, então tem que verficiar se não olhou toda a lista e n achou
            // então se o proximo não for null, então n chegou no fim ainda
            // e tbm enquanto o proximo valor n for o valor que queremos remover, continua procurando
            while (aux->next != NULL && aux->next->value != value){
                aux = aux->next;
            }
            // como citado anteriormente, n significa que o elemento a ser removido existe mesmo, então tem que verificar
            // se achou o dito cujo
            if (aux->next->value == value){
                remove = aux->next;
                aux->next = aux->next->next;
            }
        }
    }

    return remove;
}

int sum_of_evens(Node **list){
    int evens = 0;
    Node *aux;

    if (list){
        aux = *list;
        while (aux->next != NULL){
            if (aux->value % 2 == 0)
                evens = evens + aux->value;
            aux = aux->next;
        }
    }
    else
        printf("Lista vazia");

    return evens;
}

void unchain_last_node(Node **list){
    Node *aux;

    if (list){
        if ((*list)->next == NULL)
            list = NULL;
        else {
            aux = *list;
            while (aux->next->next != NULL)
                aux = aux->next;
            aux->next = NULL;
        }
    }
    else
        printf("Lista vazia");

}

int get_pos(Node **list, int value){
    Node *aux;
    int pos = 0;

    if (list){
            aux = *list;
            while (aux->next != NULL && aux->value != value){
                aux = aux->next;
                pos++;
            }

            if (aux->value == value)
                return pos;
            else
                return -1;

    }
    else
        printf("Lista vazia");

    return -1;
}

void merge_list(Node **l1, Node **l2){
    Node *aux = *l2;

    if (l1 && l2){
        if (*l1 == NULL)
            *l1 = *l2;
        else{
            while (aux){
                insert_at_end(l1, aux->value);
                aux = aux->next;
            }
        }
    }
    else
        printf("Lista vazia");

    l2 = NULL;
}

void reverse_list(Node **list){
    Node *aux, *prev = NULL;

    if (list){
        aux = *list;
        while (aux){
            *list = aux->next;
            aux->next = prev;
            prev = aux;
            aux = *list;
        }
        *list = prev;
    }
}

void merge_sorted_list(Node **l1, Node **l2){
    // tanto faz se é duplamente ou simplismente encadeada, já que ambas as listas vem já ordenadas
    Node *aux = *l2;

    if (l1 && l2){
        if (*l1 == NULL)
            *l1 = *l2;
        else{
            while (aux){
                insert_in_order(l1, aux->value);
                aux = aux->next;
            }
        }
    }
    else
        printf("Lista vazia");

    l2 = NULL;
}


void remover_pares(Node **lista, Node **pilha){
    Node *aux, *aux2;
    if (*lista){
        aux = *lista;
        while (aux->next != NULL){
            Node * new_node = (Node *) malloc(sizeof(Node));
            while (aux2->next != NULL)
                aux2 = aux2->next;
            new_node->value = aux->value;
            aux2->next = new_node;
            new_node->next = NULL;
            aux->prev = aux->prev->prev;
            aux->next = aux->next->next;
        }
    }
}

void desempilhar(Node **pilha){
    Node *aux;
    if (*pilha){
        aux = *pilha;
        while (aux->next != NULL){
            printf("%d -> ", aux->value);
            aux = aux->next;
            aux->prev->next = NULL;
        }
    }
}