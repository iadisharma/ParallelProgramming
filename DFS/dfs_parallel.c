#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<omp.h>
#define MAX_VERTICES 50000

typedef struct Graph_t {
    int V;
    bool adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

Graph* Graph_create(int V)
{
    Graph* g = malloc(sizeof(Graph));
    g->V = V;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            g->adj[i][j] = false;
        }
    }

    return g;
}

void Graph_destroy(Graph* g)
{ 
    free(g); 
}

void Graph_addEdge(Graph* g, int v, int w)
{
    g->adj[v][w] = true; 
}

void Graph_DFS(Graph* g, int s, bool visited[])
{
    visited[s] = true;
    printf("%d ", s);
    #pragma omp for
    for (int adjecent = 0; adjecent < g->V; adjecent++) {
        if (g->adj[s][adjecent] && !visited[adjecent]) {
            Graph_DFS(g, adjecent, visited);
        }
    }
}

int main()
{
    Graph* g = Graph_create(7);
    Graph_addEdge(g, 0, 1);
    Graph_addEdge(g, 0, 2);
    Graph_addEdge(g, 1, 3);
    Graph_addEdge(g, 1, 4);
    Graph_addEdge(g, 2, 5);
    Graph_addEdge(g, 2, 6);

    printf("Following is Depth First Traversal:\n");
    double start, end;
    start = omp_get_wtime();
    bool visited[MAX_VERTICES] = { false };
    #pragma omp single nowait
    {
    	Graph_DFS(g, 0, visited);
    }	
    end = omp_get_wtime();
    printf("\nExecution time of serial dfs: %f\n", end - start);
    Graph_destroy(g);

    return 0;
}

