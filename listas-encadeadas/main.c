// EXERCICIOS

/**
    * 1. Implemente uma pilha utilizando listas encadeadas. Você
deve implementar as funções Vazia, Push e Pop.
    * 2. Escrever um programa que leia um número indeterminado
de valores inteiros. O valor 0 (zero) finaliza a entrada de
dados. Para cada valor lido, determinar se ele é um número
par ou ímpar. Se o número for par, então incluí-lo na
PILHA PAR; caso contrário, incluí-lo na PILHA ÍMPAR.
Após o término da entrada de dados, retirar cada elemento
de cada PILHA e imprimi-lo.
    * 3. Implementar uma função que recebe duas pilhas p e q,
implementadas com listas encadeadas, como parâmetro,
sendo que a pilha q está vazia. Você deve transferir todos
os elementos de p para q de maneira que q seja uma cópia
idêntica de p.
 *
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

void push(Node *stack, int value);
int pop(Node *stack);
void void_stack(Node **stack);
void print_stack(Node *stack);
Node * create_stack();
void even_or_odd();
void copy_stack(Node *stack, Node *new_stack);


int main(){
    int opt, value;

    Node *stack = create_stack();

    do {
        printf("\n\t\n\t1 - Push\n\t2 - Pop\n\t3 - Limpar\n\t4 - Imprimir\n\t5 - Par e Impar\n\t0 - Sair");
        scanf("%d", &opt);

    switch(opt){
        case 1:
            printf("Digite um valor: ");
            scanf("%d", &value);
            push(stack, value);
            break;
        case 2:
            printf("Removido o valor %d", pop(stack));
            break;
        case 3:
            void_stack(&stack);
            break;
        case 4:
            print_stack(stack);
            break;
        case 5:
            even_or_odd();
            break;
        default:
            printf("Opção inválida!");
            break;
        }
    }
    while (opt !=  0);
    return 0;
}

Node * create_stack(){
    Node * head = (Node *) malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

void push(Node *stack, int value){
    if (stack) {
        Node *new_stack = (Node *) malloc(sizeof(Node));
        new_stack->value = value;
        new_stack->next = stack->next;
        stack->next = new_stack;
    }
}

int pop(Node *stack){
    int value = 0;

    if (stack != NULL){
        Node *aux = stack->next;
        value = aux->value;
        stack->next = aux->next;
        free(aux);
        return value;
    }
    else{
        printf("Pilha vazia!");
        return -1;
    }
}

void void_stack(Node **stack){
    if (*stack){
        free((*stack)->next);
        (*stack)->next = NULL;
    }
}

void print_stack(Node *stack){
    stack = stack->next;

    while (stack){
        printf("[ %d ] -> ", stack->value);
        stack = stack->next;
    }
}

void even_or_odd(){
    Node *new_stack = create_stack();
    Node *even_stack = create_stack();
    Node *odd_stack = create_stack();

    int value;
    do {
        printf("Digite um valor: ");
        scanf("%d", &value);
        push(new_stack, value);
    } while (value != 0);

    // remover o 0
    pop(new_stack);

    while (new_stack->next != NULL){
        value = pop(new_stack);
        if (value % 2 == 0){
            push(even_stack, value);
        }
        else{
            push(odd_stack, value);
        }
    }

    printf("\nPilha par: ");
    print_stack(even_stack);
    printf("\nPilha impar: ");
    print_stack(odd_stack);
}

void copy_stack(Node *stack, Node *new_stack){
    while (stack->next != NULL){
        push(new_stack, pop(stack));
    }
}