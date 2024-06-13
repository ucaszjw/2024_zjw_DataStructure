#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DFS(int **G, int numV, int visited[], int start, int end);
int main(){
    int numV;
    scanf("%d", &numV);
    int **G = malloc(numV * sizeof(int *));
    for (int i = 0; i < numV; i++){
        G[i] = malloc(numV * sizeof(int));
        for (int j = 0; j < numV; j++)
            G[i][j] = 0;
    }
    do{
        int v,w;
        scanf("%d-%d", &v, &w);
        G[v-1][w-1] = 1;
    }while (getchar() != '\n');

    int start, end;
    scanf(" %d,%d", &start, &end);
    int visited[numV];
    for (int i = 0; i < numV; i++)
        visited[i] = 0;
    visited[start-1] = 1;
    DFS(G, numV, visited, start, end);
    printf("%s\n", (visited[end-1] == 1) ? "yes" : "no");
    return 0;
}

void DFS(int **G, int numV, int visited[], int start, int end){
    for (int i = 0; i < numV; i++){
        if (G[start-1][i] == 1 && visited[i] == 0){
            visited[i] = 1;
            DFS(G, numV, visited, i+1, end);
        }
    }
    return;
}