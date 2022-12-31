/*
 Resolução do exercicio de implementação de caminhos minimos em grafos
 Aluno: Micael Muniz
 Data de finalização: 15/12/2022

 Algoritmo utilizado: Dijkstra
 Grafo utilizado: Matriz de adjacencia, direcionado
 Nome do arquivo lido: "voos.txt" (deve estar na mesma pasta do programa)
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_CITIES 9
#define MAX_FLIGHTS 10 // Mude isso caso utilize um arquivo com mais voos
#define INFINITY 9999

// Estrura para guardar as cidades (vértices)
typedef struct {
    int code;
    char *name;
} City;

// Estrutura para guardar os voos (arestas)
typedef struct {
    int code;
    int source;
    int destination;
    int duration;
} Flight;

// Estrutura para guardar o grafo (lista de adjacências)
typedef struct node {
    int cityCode;
    struct node *next;
} Node;

// Arrays globais para guardar as cidades e os voos
City cities[MAX_CITIES];
Flight flights[MAX_FLIGHTS];

City findCity(int code);
void insertAtBeginning(Node **head, int cityCode);
void printPath(Node *head);
void freePath(Node *head);
void dijkstra(int source, int destination);

int main() {
    // Inicia lista de cidades
    const char *cityNames[MAX_CITIES] = {"Joy", "Hope", "Friendship", "Surprise", "Honesty", "Wonderland", "Optimism", "Confidence", "Happiness"};
    for (int i = 0; i < MAX_CITIES; i++) {
        cities[i] = (City){i, cityNames[i]};
    }

    // Le os voos através do arquivo "voos.txt" (cria as arestas)
    FILE *fp = fopen("voos.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    int code, source, destination, duration;
    int i = 0;
    while (fscanf(fp, "%d %d %d %d", &code, &source, &destination, &duration) == 4) {
        flights[i].code = code;
        flights[i].source = source;
        flights[i].destination = destination;
        flights[i].duration = duration;
        i++;
    }
    fclose(fp);

    // Le o código da cidade de destino do usuário
    int destinationCode;
    printf("Bem vindo ao sistema de voos da Good Feelings Airlines!\n");
    printf("Insira a cidade de destino: ");
    scanf("%d", &destinationCode);

    // Validações de entradas
    if (destinationCode == 0) {
        printf("Voce ja esta na cidade de destino.\n");
        return 1;
    }
    if (destinationCode < 0 || destinationCode >= MAX_CITIES) {
        printf("Codigo de cidade invalido! \nVerifique a tabela de cidades e seus respectivos codigos da nossa companhia aerea!\n");
        return 1;
    }

    // Encontre o caminho minimo entre a cidade de Joy (0) e a cidade de destino
    dijkstra(0, destinationCode);

    return 0;
}


// Função para ler a cidade através do codigo fornecido
City findCity(int code) {
    for (int i = 0; i < MAX_CITIES; i++) {
        if (cities[i].code == code) {
            return cities[i];
        }
    }
    // Caso não encontre a cidade, retorna uma cidade com código -1, ou seja, inválido.
    return (City){-1, "Cidade não encontrada"};
}


// Função para inserir um novo nó na lista de adjacências
void insertAtBeginning(Node **head, int cityCode) {
    Node *newNode = malloc(sizeof(Node));
    newNode->cityCode = cityCode;
    newNode->next = *head;
    *head = newNode;
}

// Função para imprimir o caminho
void printPath(Node *head) {
    if (head == NULL) {
        printf("Nenhum caminho encontrado.\n");
    } else {
        printf("Voce passara pelas cidades: ");
        while (head != NULL) {
            printf("%s -> ", findCity(head->cityCode).name);
            head = head->next;
        }
        printf("\n");
    }
}

// Libera a memória alocada para o caminho
void freePath(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

// Função para implementar o algoritmo de Dijkstra
void dijkstra(int source, int destination) {
    // Array para armazenar a distancia minima
    int minDistance[MAX_CITIES];
    // Array para armazenar a cidade anterior no caminho para cada cidade
    int previous[MAX_CITIES];
    // Array para armazenar as cidades visitadas
    int visited[MAX_CITIES];
    // Array para armazenar os vooos utilizados
    int usedFlights[MAX_CITIES];

    // Inicializa os arrays
    for (int i = 0; i < MAX_CITIES; i++) {
        minDistance[i] = INFINITY;
        previous[i] = -1;
        visited[i] = 0;
    }
    // Seta a distancia minima da cidade de origem como 0
    minDistance[source] = 0;

    // Enquanto todas as cidades não forem visitadas
    while (1) {
        // Encontra a cidade não visitada com a menor distancia
        int minDistanceCity = -1;
        for (int i = 0; i < MAX_CITIES; i++) {
            if (!visited[i] && (minDistanceCity == -1 || minDistance[i] < minDistance[minDistanceCity])) {
                minDistanceCity = i;
            }
        }
        // Se todas as cidades foram visitadas ou não há caminho para nenhuma outra cidade, quebre o loop
        if (minDistanceCity == -1) {
            break;
        }

        // Marca a cidade como visitada
        visited[minDistanceCity] = 1;

        // Atualiza a distancia minima para as cidades adjacentes
        for (int i = 0; i < MAX_FLIGHTS; i++) {
            Flight flight = flights[i];
            if (flight.source == minDistanceCity) {
                int newDistance = minDistance[minDistanceCity] + flight.duration;
                if (newDistance < minDistance[flight.destination]) {
                    minDistance[flight.destination] = newDistance;
                    previous[flight.destination] = minDistanceCity;
                    usedFlights[flight.destination] = flight.code;
                }
            }
        }
    }

    // Cria uma lista de caminho para armazenar o caminho da origem para o destino
    Node *path = NULL;
    int cityCode = destination;
    while (cityCode != -1) {
        insertAtBeginning(&path, cityCode);
        cityCode = previous[cityCode];
    }

    // Imprime o tempo minimo e o caminho para o destino
    if (minDistance[destination] == INFINITY) {
        printf("Nenhum caminho encontrado.\n");
    } else {
        printf("\nMenor tempo para %s: %d minutos\n", findCity(destination).name, minDistance[destination]);
        printPath(path);

        printf("Sendo necessario utilizar os voos: ");
        path = path->next;
        while (path != NULL) {
            printf("%d -> ", usedFlights[path->cityCode]);
            path = path->next;
        }
    }

    // Libera a memória alocada para o caminho
    freePath(path);
}
