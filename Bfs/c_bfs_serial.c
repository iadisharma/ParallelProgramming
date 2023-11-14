  #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

typedef struct queue
{
    int front, rear, size;
    unsigned capacity;
    int *arr;
} queue;

queue *createQueue(unsigned capacity)
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->capacity = capacity;
    q->front = q->size = 0;
    q->rear = capacity - 1;
    q->arr = (int *)malloc(q->capacity * sizeof(int));
    return q;
}

bool isFull(queue *q)
{
    return (q->size == q->capacity);
}

bool isEmpty(queue *q)
{
    return (q->size == 0);
}

void enqueue(queue *q, int item)
{
    if (isFull(q))
        return;
    q->rear = (q->rear + 1) % q->capacity;
    q->arr[q->rear] = item;
    q->size = q->size + 1;
}

int dequeue(queue *q)
{
    if (isEmpty(q))
        return -1;
    int item = q->arr[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size = q->size - 1;
    return item;
}

void bfs(int **adj, int v, int sv, bool *visited)
{
    queue *q = createQueue(v);
    enqueue(q, sv);
    visited[sv] = true;

    while (!isEmpty(q))
    {
        int f = dequeue(q);
        printf("%d ", f);
        for (int i = 0; i < v; i++)
        {
            if (i == f)
            {
                continue;
            }
            if (adj[f][i] == 1)
            {
                if (visited[i])
                {
                    continue;
                }
                else
                {
                    enqueue(q, i);
                    visited[i] = true;
                }
            }
        }
    }
}

int main()
{
    int v, e;
    printf("Enter number of vertices\n");
    scanf("%d", &v);
    printf("Enter number of Edges\n");
    scanf("%d", &e);

    int **adj = (int **)malloc(v * sizeof(int *));
    for (int i = 0; i < v; i++)
    {
        adj[i] = (int *)malloc(v * sizeof(int));
        for (int j = 0; j < v; j++)
        {
            adj[i][j] = 0;
        }
    }
    for (int i = 0; i < e; i++)
    {
        int f, s;
        printf("Enter vertices where an edge is present s and e vertex\n");
        scanf("%d %d", &f, &s);
        adj[f][s] = 1;
        adj[s][f] = 1;
    }
    bool *vis = (bool *)malloc(v * sizeof(bool));
    for (int i = 0; i < v; i++)
    {
        vis[i] = false;
    }
    double t1, t2;
    t1 = omp_get_wtime();
    bfs(adj, v, 0, vis);
    t2 = omp_get_wtime();
    printf("The execution time is-: %f\n", (t2 - t1));
    return 0;
}



