#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Graph{
    int connect;
    int distance;
};

void DFS(struct Graph **G, int numV, int visited[],int distance[], int start, int end);
int main(){
    int numV;
    scanf("%d", &numV);
    struct Graph **G = malloc(numV * sizeof(struct Graph *));
    for (int i = 0; i < numV; i++){
        G[i] = malloc(numV * sizeof(struct Graph));
        for (int j = 0; j < numV; j++){
            G[i][j].connect = 0;
            G[i][j].distance = -1;
        }
    }
    do{
        int v,w;
        scanf("%d-%d", &v, &w);
        G[v-1][w-1].connect = 1;
    }while (getchar() != '\n');

    for (int start = 1; start <= numV; start++){
        for (int end = 1; end <= numV; end++){
            int visited[numV];
            int distance[numV];
            for(int i = 0; i < numV; i++){
                visited[i] = 0;
                distance[i] = -1;
            }
            visited[start-1] = 1;
            distance[start-1] = 0;
            DFS(G, numV, visited, distance, start, end);
            G[start-1][end-1].distance = distance[end-1];      
        }
    }

    int maxdst[numV];
    for (int i = 0; i < numV; i++){
        maxdst[i] = 0;
        for (int j = 0; j < numV; j++){
            if (G[i][j].distance > maxdst[i]){
                maxdst[i] = G[i][j].distance;
            }
        }
    }

    printf("%d", maxdst[0]);
    for (int i = 1; i < numV; i++)
        printf(",%d", maxdst[i]);
    printf("\n");
    return 0;
}

void DFS(struct Graph **G, int numV, int visited[],int distance[], int start, int end){
    for (int i = 0; i < numV; i++){
        if (G[start-1][i].connect == 1 && visited[i] == 0){
            visited[i] = 1;
            distance[i] = distance[start-1] + 1;
            DFS(G, numV, visited, distance, i+1, end);
        }
    }
    return;
}