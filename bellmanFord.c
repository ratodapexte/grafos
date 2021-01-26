#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int V, E;

    struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph) );

    graph->V = V;
    graph->E = E;

    graph->edge = (struct Edge*) malloc( graph->E * sizeof( struct Edge ) );

    return graph;
}

void printArr(int dist[], int n)
{
    printf("Distância de um vértice v para a origem:\n");
    int i;

    for (i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void BellmanFord(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int dist[V];
    int i,j;

    for (i = 0; i < V; i++)
        dist[i]   = INT_MAX;

    dist[src] = 0;

    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;

            if (dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    for (i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;

        if (dist[u] + weight < dist[v])
            printf("Grafo contém cíclo de peso negativo");
    }

    printArr(dist, V);
}

int main()
{
    int V, E, i;  

    printf("Digite o número de vértices:\n");
    scanf("%d",&V);
    
    printf("Digite o número de arestas:\n");
    scanf("%d",&E);

    struct Graph* graph = createGraph(V, E);

    printf("Digite os vértices da aresta e o seu peso:\n Exemplo: Aresta[x]: v1 v2 custo\n");

    for(i=0;i<E;i++){
        printf("Aresta[%d]: ", i);
        scanf("%d",&graph->edge[i].src);
        scanf("%d",&graph->edge[i].dest);
        scanf("%d",&graph->edge[i].weight);
    }
    
    int parent[V];

    BellmanFord(graph, 0);

    return 0;
}