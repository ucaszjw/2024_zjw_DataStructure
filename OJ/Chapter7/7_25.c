#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void DFS(int **G, int numV, int visited[], int start, int end);
int main(){
    int numV;
    scanf("%d", &numV);
    int s[MAX] = {0}, fst[numV+1], lst[numV+1];
    int **G = malloc(numV * sizeof(int *));
    for (int i = 0; i < numV; i++){
        G[i] = malloc(numV * sizeof(int));
        for (int j = 0; j < numV; j++)
            G[i][j] = 0;        
    }
    do{
        static int i = 0;
        scanf("%d", &s[i]);
        i++;
    } while (getchar() != '\n'); 
    
    for (int i = 0; i < numV+1; i++)
        scanf("%d", &fst[i]);
    for (int i = 0; i < numV+1; i++)
        scanf("%d", &lst[i]);    
    
    for (int i = 1; i <= numV; i++){
        if (fst[i] > lst[i])
            continue;
        for (int index = fst[i]; index < lst[i]; index++){
            G[i-1][s[index]-1] = 1;
        }
    }
    int start;
    int cycle = 0;
    for (int start = 1; start <= numV; start++){
        int visited[numV];
        for (int i = 0; i < numV; i++)
            visited[i] = 0;
        DFS(G, numV, visited, start, start);
        if (visited[start-1] == 1){
            cycle = 1;
            break;
        }
    }
    printf("%s\n", (cycle == 1) ? "yes" : "no");
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