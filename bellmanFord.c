
#include <stdio.h>
#include <limits.h>   


void BellmanFord(int grafo[][3], int vertice, int aresta,
                 int origem)
{

    int dis[vertice];
    for (int i = 0; i < vertice; i++)
    {
        dis[i] = INT_MAX;
    }       
 

    dis[origem] = 0;
 

    for (int i = 0; i < vertice - 1; i++) 
    {
 
        for (int j = 0; j < aresta; j++) 
        {
            if (dis[grafo[j][0]] != INT_MAX && dis[grafo[j][0]] + grafo[j][2] <
                               dis[grafo[j][1]])
                dis[grafo[j][1]] = 
                  dis[grafo[j][0]] + grafo[j][2];
        }
    }
 

    for (int i = 0; i < aresta; i++) 
    {
        int x = grafo[i][0];
        int y = grafo[i][1];
        int peso = grafo[i][2];
        if (dis[x] != INT_MAX && dis[x] + peso < dis[y]) 
        {
            printf("O Grafo contém Ciclo de Peso Negativo"); 
        }
        
    }
 
    printf("Distância do Vértice para a Origem\n");

    for (int i = 0; i < vertice; i++)
    {
         printf("Vértice %d dist %d\n",i,dis[i]);
    }
        
}
 
int main()
{
    int i, j, n, e, c, v1, v2;

    printf("Digite a quantidade de vértices:\n");
    scanf("%d", &n);

    printf("Digite o número de arestas:\n");
    scanf("%d",&e);

    int grafo[e][3];

    printf("Digite os vértices da aresta e o seu peso:\n Exemplo: Aresta[x]: v1 v2 custo\n");
    for(i = 0; i < e; i++)
    {
        printf("Aresta[%d]: ", i);
        scanf(" %d %d %d", &v1, &v2, &c);
        grafo[i][0] = v1;
        grafo[i][1] = v2;
        grafo[i][2] = c;

    }

    printf("Digite o vértice de origem entre 0 - n: ");
    int origem;
    scanf("%d", &origem);
 
    BellmanFord(grafo, n, e, origem);
    return 0;
}