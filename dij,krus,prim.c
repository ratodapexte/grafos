#include <limits.h>  
#include <stdio.h>
#include <stdbool.h>

int gAux; 

// this method returns a minimum distance for the 
// vertex which is not included in Tset.
int minimumDist(int dist[], int Tset[], int n) 
{
	int i,min=INT_MAX,index;
              
	for(i = 0; i < n; i++) 
	{
		if(Tset[i] == 0 && dist[i] <= min)      
		{
			min = dist[i];
			index = i;
		}
	}
	return index;
}

void Dijkstra(int graph[][gAux],int src, int target, int n) // adjacency matrix used is 6x6
{
	int i, dist[n], Tset[n], prev[n]; // integer array to calculate minimum distance for each node.                            
	
	// set the nodes with infinity distance
	// except for the initial node and mark
	// them unvisited.  
	for(i = 0; i < n; i++)
	{
		dist[i] = INT_MAX;
		Tset[i] = 0;	
	}
	
	dist[src] = 0;   // Source vertex distance is set to zero.             
	printf("Max: %d\n", INT_MAX);

	// for(int i = 0; i<6; i++)                           
	while(Tset[target] == 0)
	{
		int m=minimumDist(dist,Tset, n); // vertex not yet included.
		Tset[m]=1;// m with minimum distance included in Tset.
		for(i = 0; i< n; i++)                  
		{
			// Updating the minimum distance for the particular node.
			if(!Tset[i] && graph[m][i] != INT_MAX && dist[m]!=INT_MAX && dist[m]+graph[m][i]<dist[i])
			{
				dist[i]=dist[m]+graph[m][i];
				prev[i] = m;
			}
		}
		printf("Aresta[%d][%d]\n", m, i);
	}
	printf("Distancia do vértice %d ateh o vertice %d foi %d\n", src, target, dist[target]);

	printf("%d ->",target);
	int check = target;

	while(check != src)
	{
		check = prev[check];
		if(check == src)
			printf(" %d", check);
		else
			printf(" %d ->", check);
	}
	printf("\n");
		// for(int i = 0; i<6; i++)                      
	// { //Printing
	// 	char str=65+i; // Ascii values for pritning A,B,C..
	// 	cout<<str<<"\t\t\t"<<dist[i]<<endl;
	// }
}

// Find set of vertex i 
int find(int i, int *parent) 
{ 
	while (parent[i] != i) 
		i = parent[i]; 
	return i; 
} 

// Does union of i and j. It returns 
// false if i and j are already in same 
// set. 
void union1(int i, int j, int *parent) 
{ 
	int a = find(i, parent); 
	int b = find(j, parent); 
	parent[a] = b; 
} 

// Finds MST using Kruskal's algorithm 
void kruskalMST(int custo[][gAux], int *parent, int n) 
{ 
	int min = 0, i, j; // custo of min MST. 

	// Initialize sets of disjoint sets. 
	for (i = 0; i < n; i++) 
		parent[i] = i; 

	// Include minimum weight edges one by one 
	int arestaCont = 0; 
	while (arestaCont < n - 1) { 
		int min = INT_MAX, a = -1, b = -1; 
		for (i = 0; i < n; i++) { 
			for (j = 0; j < n; j++) { 
				if (find(i, parent) != find(j, parent) && custo[i][j] < min) { 
					min = custo[i][j]; 
					a = i; 
					b = j; 
				} 
			} 
		} 

		union1(a, b, parent); 
		printf("Aresta %d:(%d, %d) custo:%d \n", 
			arestaCont++, a, b, min); 
		min += min; 
	} 
	printf("\n Custo mínimo = %d \n", min); 
}

void prim(int v, int matrix[][gAux]) 
{
    // resultado[v][1] = resultado[v][0] = 0;
    int custo[gAux], anterior[gAux], visitados[gAux], u, a;

    for(u = 0; u < gAux; u++)
    {
        custo[u] = INT_MAX;
        visitados[u] = anterior[u] = -1;
    }
    custo[v] = 0;
    anterior[v] = v;


    while(true)
    {    
        int aux = INT_MAX;
        visitados[v] = 1;
        for(u = 0; u < gAux; u++)
        {
            if(matrix[v][u] < custo[u] && matrix[v][u] != INT_MAX && visitados[u] != 1)
            {
                custo[u] = matrix[v][u];
                anterior[u] = v;
            }
        }

        for(a = 0; a < gAux; a++) // busca do vértice com o menor total e ainda não visitado
            if(visitados[a] != 1)
                if(custo[a] < aux)
                {
                    v = a;
                    aux = custo[a];
                }

        if(visitados[v] == 1) break;
    }   

    printf("Caminho do Grafo: ");

    for(a = 0; a < gAux; a++)
    {
        printf("(%d, %d), ", a, anterior[a]);
    }

    printf("\n\nTabela Dada:\nvertices   : ");

    for(a = 0; a < gAux; a++)
    {
        printf("%d  |", a);
    }

    printf("\ndistancia  : ");

    for(a = 0; a < gAux; a++) 
    {
        printf("%d  |", custo[a]);
    }
        
    printf("\nvertice anterior: ");

    for(a = 0; a < gAux; a++)
    {
        printf("%d  |", anterior[a]);

    }
    
    printf("\n\n");    
}

int main()
{
	int i, j, n = 0, e, c, v1, v2;

	printf("Digite a quantidade de vértices:\n");
	scanf("%d", &n);

	gAux = n;

	int graph[n][n];

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{	
			grafo[i][j] = INT_MAX;
		}
	}

	printf("Digite o número de arestas:\n");
	scanf("%d",&e);

	printf("Digite os vértices da aresta e o seu peso:\n Exemplo: Aresta[x]: v1 v2 custo\n");
	for(i = 0; i < e; i++)
	{
		printf("Aresta[%d]: ", i);
		scanf("%d %d %d", &v1, &v2, &c);
		grafo[v1][v2] = c;
		grafo[v2][v1] = c;

	}

	int parent[gAux], opcao = 0, flag = 1;

	// int graph[][9] = {
	// 	{INT_MAX, 3, INT_MAX, 2, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 4},
	// 	{3, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 4, INT_MAX},
	// 	{INT_MAX, INT_MAX, INT_MAX, 6, INT_MAX, 1, INT_MAX, 2, INT_MAX},
	// 	{2, INT_MAX, 6, INT_MAX, 1, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
	// 	{INT_MAX, INT_MAX, INT_MAX, 1, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8},
	// 	{INT_MAX, INT_MAX, 1, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX, INT_MAX},
	// 	{INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX, INT_MAX, INT_MAX},
	// 	{INT_MAX, 4, 2, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 8},
	// 	{4, INT_MAX, INT_MAX, INT_MAX, 8, INT_MAX, INT_MAX, INT_MAX, INT_MAX}};

	// int graph[][8]={
 //        {INT_MAX,2,INT_MAX,6,5,INT_MAX,INT_MAX,INT_MAX},
 //        {2,INT_MAX,7,7,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
 //        {INT_MAX,7,INT_MAX,INT_MAX,6,2,INT_MAX,INT_MAX},
 //        {6,7,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX,INT_MAX},
 //        {5,INT_MAX,6,INT_MAX,INT_MAX,INT_MAX,4,5},
 //        {INT_MAX,INT_MAX,2,INT_MAX,INT_MAX,INT_MAX,4,6},
 //        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,4,4,INT_MAX,1},
 //        {INT_MAX,INT_MAX,INT_MAX,INT_MAX,5,6,1,INT_MAX},
	// };


	printf("ALGORITMOS\n");
	printf("Selecione uma das opções. Para cacncelar digite qualquer outro valor.\n");

	while(flag == 1)
	{
		printf("1 - Dijkstra;\n2 - Kruskal\n3 - Prim\nOpção: ");
		scanf("%d", &opcao);

		switch(opcao)
		{
			case 1:
				printf("Digite o vértice de origem entre 0 - n: ");
				int origem;
				scanf("%d", &origem);

				printf("Digite o vértice alvo entre 0 - n: ");
				int alvo;
				scanf("%d", &alvo);				
				Dijkstra(graph,origem,alvo,n);
				break;

			case 2:
				kruskalMST(graph, parent, n);
				break;

			case 3:
				printf("Digite o vértice de origem entre 0 - n: ");
				int origem;
				scanf("%d", &origem);
	
				prim(origem, graph);
				break;

			default:	
				flag = -1;
		}
	}

	return 0;	                        
}

