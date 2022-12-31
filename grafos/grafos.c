// 1. Complete o programa GrafoMatriz.c inserindo as seguintes funções:
// Por Micael Muniz - 26/11/2022

#include "MGrafo.h"

// versão alternativa mais completa de um grafo
typedef struct grafo{
    int ponderado;      // se tem peso, valores: 1 ou 0 (booleano)
    int nro_vertices;   // quantidade de bolinhas q tem (tamanho do vetor), vertices
    int grau_max;       // quantos parentes tem, quantidade de amigos, quantas arestas sai dele
    int** arestas;      // uma lista para cada vértice
    float** pesos;      // lista com os pesos
    int* grau;          // grau daquela vértice, mesma ID do nro_vertices
} MGrafo;

// versão utilizada na sala de aula
typedef struct{
  int n;
  int **Adj;
} Grafo;



//a. Imprime a lista de adjacentes de um dado vértice u.
void ImprimeListaAdjacencia (Grafo G, int u){
    int v;

    printf ("\nVertice %d: ", u);
    for (v = 0; v < G.n; v++)
        if (G.Adj[u][v] == 1)
            printf ("%d ", v);
}


//b. Calcula o grau de um dado vértice através de uma função;
int CalculaGrau (Grafo G, int u){
    int v, grau = 0;

    for (v = 0; v < G.n; v++)
        if (G.Adj[u][v] == 1)
            grau++;
    return grau;
}


// c. Calcula o grau máximo e o grau mínimo de um grafo;
void CalculaGrauMaxMin (Grafo G){
    int u, grau, grauMax = 0, grauMin = G.n;

    for (u = 0; u < G.n; u++){
        grau = CalculaGrau(G, u);
        if (grau > grauMax)
            grauMax = grau;
        if (grau < grauMin)
            grauMin = grau;
    }

    printf("\nGrau maximo: %d", grauMax);
    printf("\nGrau minimo: %d", grauMin);
}


//d. Calcule o grau de entrada e o grau de saída de um dado vértice;
void CalculaGrauEntradaSaida (Grafo G, int u){
    int v, grauEntrada = 0, grauSaida = 0;

    for (v = 0; v < G.n; v++){
        if (G.Adj[u][v] == 1)
            grauSaida++;
        if (G.Adj[v][u] == 1)
            grauEntrada++;
    }

    printf("\nGrau de entrada: %d", grauEntrada);
    printf("\nGrau de saida: %d", grauSaida);
}


// e. Ler n inteiros e dizer se é uma sequência de vértices representando um caminho no grafo.
int ehCaminho(Grafo G){
    if (G.n == 0)
        return 0;
    else{
        int* visitados = (int*) malloc (G.n * sizeof (int));
        int v, i = 0;

        while (i < G.n){
            // le a sequencia até que digite -1 ou até que a sequencia seja maior que o numero de vertices
            scanf(" %d", &v);
            if (v < 0)
                break;
            // guarda no vetor todos valores digitados pela pessoa
            visitados[i] = v;
            i++;
        }
        // utiliza a lista que foi criada com os valores digitados para descobrir se é um caminho
        for (i = 0; i < G.n - 1; i++){
            if (G.Adj[visitados[i]][visitados[i+1]] == 0)
                // se descobrir qualquer um que não tenha relação, retorna 0 (false)
                return 0;
        }
        // se não retornou 0, é porque é um caminho, 1 (True)
        return 1;
    }
}
