#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 1000  // 最大顶点数

typedef struct Node {
    int vertex;
    int weight;
    struct Node *next;
} Node;

Node *graph[MAX_VERTICES];
int dist[MAX_VERTICES];
int visited[MAX_VERTICES];

void addEdge(int u, int v, int w) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = graph[u];
    graph[u] = newNode;
}

void dijkstra(int src, int n) {
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INT_MAX, min_index;
        for (int v = 0; v < n; v++)
            if (!visited[v] && dist[v] <= min)
                min = dist[v], min_index = v;

        int u = min_index;
        visited[u] = 1;

        for (Node *p = graph[u]; p != NULL; p = p->next)
            if (!visited[p->vertex] && dist[u] != INT_MAX && dist[u] + p->weight < dist[p->vertex])
                dist[p->vertex] = dist[u] + p->weight;
    }
}

int main() {
    int n, src;
    scanf("%d %d", &n, &src);
    src--; 
    while (!feof(stdin)) {
        int u, v, w;
        if (scanf("%d-%d %d", &u, &v, &w) != 3) break;
        addEdge(u - 1, v - 1, w);  
        addEdge(v - 1, u - 1, w); 
    }
    dijkstra(src, n);
    for (int i = 1; i < n; i++)
        if (dist[i] == INT_MAX)
            ;
        else
            if(i != n-1)
                printf("%d,", dist[i]);
            else
                printf("%d\n", dist[i]);

    return 0;
}