#include <stdio.h>
#include <stdlib.h>

void DFS(int **G, int numV, int visited[],int distance[], int start, int end);
int main(){
    int numV, k;
    int start, end;
    int **G;
    scanf("%d,%d", &numV, &k);
    scanf("%d,%d", &start, &end);
    G = (int **)malloc(sizeof(int *) * numV);
    for(int i = 0; i < numV; i++){
        G[i] = (int *)malloc(sizeof(int) * numV);
        for(int j = 0; j < numV; j++){
            G[i][j] = 0;
        }
    }
    do{
        int v1, v2;
        scanf("%d-%d", &v1, &v2);
        G[v1-1][v2-1] = 1;
    } while (getchar() != '\n');

    int visited[numV];
    int distance[numV];
    for(int i = 0; i < numV; i++){
        visited[i] = 0;
        distance[i] = -1;
    }
    visited[start-1] = 1;
    distance[start-1] = 0;
    DFS(G, numV, visited, distance, start, end);
    printf("%s\n", visited[end-1] == 1 && distance[end-1] == k ? "yes" : "no");
    return 0;
}

void DFS(int **G, int numV, int visited[],int distance[], int start, int end){
    for (int i = 0; i < numV; i++){
        if (G[start-1][i] == 1 && visited[i] == 0){
            visited[i] = 1;
            distance[i] = distance[start-1] + 1;
            DFS(G, numV, visited, distance, i+1, end);
        }
    }
    return;
}