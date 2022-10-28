#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node *left, *right;
}Node;


//void insertRight(Node *node, int value);
//void insertLeft(Node *node, int value);
//void insert(BTree *tree, int value);
void print_tree(Node *root);
int count_nodes(Node * root);
int height(Node * root);
Node* alt_insert(Node *raiz, int value);
int search(Node *root, int key);
Node* remove_node(Node *root, int key);
int remove_smallest_value_between_x_and_r(Node *r, int x);
int remove_smallest(Node *root);



int main() {
    int option, value;
    Node* root = NULL;

    do{
        printf("\n0 - Saiur\n1 - Inserir\n2 - Imprimir\n3 - Contar nos\n4 - Altura da arvore\n5 - Buscar\n6 - Remover\n7 = Menor valor entre x e raiz\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o valor: \n");
                scanf("%d", &value);
                //insert(&tree, value);
                root = alt_insert(root, value);
                break;
            case 2:
                print_tree(root);
                break;
            case 3:
                printf("A arvore tem %d nos", count_nodes(root));
                break;
            case 4:
                printf("A arvore tem %d de altura", height(root));
                break;
            case 5:
                printf("Digite o valor: \n");
                scanf("%d", &value);
                printf("Valor achado: %d", search(root, value));
                break;
            case 6:
                printf("Digite o valor a ser removido: \n");
                scanf("%d", &value);
                root = remove_node(root, value);
                break;
            case 7:
                printf("Digite o valor: \n");
                scanf("%d", &value);
                printf("Menor valor entre %d e raiz: %d", value, remove_smallest_value_between_x_and_r(root, value));
                break;
            default:
                printf("Opcao invalida");
                break;
        }

    } while (option != 0);

    return 0;
}

/*
void insertLeft(Node *node, int value) {
    if (node->left == NULL){
        Node *new = (Node *)malloc(sizeof(Node));
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        node->left = new;
    }else{
        if (value < node->left->value)
            insertLeft(node->left, value);
        //else
        if (value > node->left->value)
            insertRight(node->left, value);
    }
}


void insertRight(Node *node, int value){
    if (node->right == NULL){
        Node *new = (Node *)malloc(sizeof(Node));
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        node->right = new;
    }else{
        if (value > node->right->value)
            insertRight(node->right, value);
        //else
        if (value < node->right->value)
            insertLeft(node->right, value);
    }
}


void insert(BTree *tree, int value){
    if (tree->root == NULL){
        Node *new = (Node*)malloc(sizeof(Node));
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        tree->root = new;
    }else{
        if (value < tree->root->value)
            insertLeft(tree->root, value);
        //else
        if (value > tree->root->value)
            insertRight(tree->root, value);
    }
}
*/

Node* alt_insert(Node *root, int value){
    if (!root){
        Node *new = (Node*)malloc(sizeof(Node));
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        return new;
    }else{
        if (value < root->value)
            root->left = alt_insert(root->left, value);
        if (value > root->value)
            root->right = alt_insert(root->right, value);
        return root;
    }
}


void print_tree(Node *root){
    if (root != NULL){
        print_tree(root->left);
        printf("%d ", root->value);
        print_tree(root->right);
    }
}


int count_nodes(Node * root){
    if (!root)
        return 0;
    else
        return 1 + count_nodes (root->left) + count_nodes (root->right);
}


int height(Node * root){
    if (!root)
        return -1;
    else{
        int hL = height(root->left);
        int hR = height(root->right);
        //return 1 + (hL > hR? hL: hR);
        if (hL > hR)
            return 1 + hL;
        else
            return 1 + hR;
    }
}

int search(Node *root, int key){
    if (!root)
        return -1;
    else{
        if (root->value == key)
            return root->value;
        else{
            if (key < root->value)
                return search(root->left, key);
            else
                return search(root->right, key);
        }
    }
}

Node* remove_node(Node *root, int key){
    if (root == NULL){
        printf("Valor não encontrado!\n");
        return NULL;
    }else{
        if (root->value == key){
            if (root->right == NULL && root->left == NULL){
                free(root);
                return NULL;
            }else{
                if (root->right != NULL && root->left != NULL){
                    Node *aux = root->left;
                    while (aux->right != NULL)
                        aux = aux->right;
                    root->value = aux->value;
                    aux->value = key;
                    root->left = remove_node(root->left, key);
                    return root;
                }else{
                    Node *aux;
                    if (root->left != NULL)
                        aux = root->left;
                    else
                        aux = root->right;
                    free(root);
                    return aux;
                }
            }
        }else{
            if (key < root->value){
                root->left = remove_node(root->left, key);
            }else{
                root->right = remove_node(root->right, key);
            }
            return root;
        }
    }
}

// Escreva uma função para verificar se uma árvore binária é uma árvore binária de busca.

void check_is_search_tree(Node *root){
    if (root != NULL){
        check_is_search_tree(root->left);
        if (root->left != NULL && root->left->value > root->value){
            printf("Nao é uma arvore de busca\n");
            return;
        }
        if (root->right != NULL && root->right->value < root->value){
            printf("Nao é uma arvore de busca\n");
            return;
        }
        check_is_search_tree(root->right);
    }
    printf("É uma arvore de busca\n");
}

// Escreva uma função recebe uma árvore binária de busca r e o valor de um nó x e retorna o valor do elemento que possui a menor chave (valor do elemento) dentre os elementos que são maiores do que x em r.

int remove_smallest(Node *root){
    if (root->left == NULL){
        int value = root->value;
        free(root);
        return value;
    }else{
        return remove_smallest(root->left);
    }
}

// Escreva uma função recebe uma árvore binária de busca r e o valor de um nó x
// e retorna o valor do elemento que possui o menor valor dentre os elementos que são maiores do que x em r.


int remove_smallest_value_between_x_and_r(Node *r, int x) {
    if (r == NULL)
        return -1;
    if (r->value > x) {
        if (r->left == NULL) {
            int value = r->value;
            free(r);
            //r = NULL;
            return value;
        }else
            return remove_smallest_value_between_x_and_r(r->left, x);
    }else
        return remove_smallest_value_between_x_and_r(r->right, x);
}