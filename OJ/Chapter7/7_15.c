#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InsertVertex(int **G, int numV, int **newG, int v);
void InsertArc(int **G, int numV, int **newG, int v, int w);
void DeleteVertex(int **G, int numV, int **newG, int v);
void DeleteArc(int **G, int numV, int **newG, int v, int w);
int main(){
    int numV;
    scanf("%d", &numV);
    int **G = malloc(numV * sizeof(int *));
    for (int i = 0; i < numV; i++){
        G[i] = malloc(numV * sizeof(int));
        for (int j = 0; j < numV; j++)
            scanf("%d", &G[i][j]);
    }

    char func[3];
    int v, w;
    int **newG = NULL;
    while (scanf(" %s %d", func, &v) != EOF){
        if (func[1] == 'A')
            scanf("%d", &w);        
        if (strcmp(func, "IV") == 0){
            numV++;
            newG = realloc(newG, numV * sizeof(int *));
            for (int i = 0; i < numV; i++)
                newG[i] = malloc(numV * sizeof(int));
            InsertVertex(G, numV, newG, v);
            G = realloc(G, numV * sizeof(int *));
            for (int i = 0; i < numV; i++)
                G[i] = malloc(numV * sizeof(int));
            for (int i = 0; i < numV; i++)
                for (int j = 0; j < numV; j++)
                    G[i][j] = newG[i][j];
        }
        else if (strcmp(func, "IA") == 0){
            newG = realloc(newG, numV * sizeof(int *));
            for (int i = 0; i < numV; i++)
                newG[i] = malloc(numV * sizeof(int));
            InsertArc(G, numV, newG, v, w);
            for (int i = 0; i < numV; i++)
                for (int j = 0; j < numV; j++)
                    G[i][j] = newG[i][j];
        }
        else if (strcmp(func, "DV") == 0){
            numV--;
            newG = realloc(newG, numV * sizeof(int *));
            for (int i = 0; i < numV; i++)
                newG[i] = malloc(numV * sizeof(int));
            DeleteVertex(G, numV, newG, v);
            G = realloc(G, numV * sizeof(int *));
            for (int i = 0; i < numV; i++)
                G[i] = malloc(numV * sizeof(int));
            for (int i = 0; i < numV; i++)
                for (int j = 0; j < numV; j++)
                    G[i][j] = newG[i][j];
        }
        else if (strcmp(func, "DA") == 0){
            newG = realloc(newG, numV * sizeof(int *));
            for (int i = 0; i < numV; i++)
                newG[i] = malloc(numV * sizeof(int));
            DeleteArc(G, numV, newG, v, w);
            for (int i = 0; i < numV; i++)
                for (int j = 0; j < numV; j++)
                    G[i][j] = newG[i][j];
        }
    }
    for (int i = 0; i < numV; i++){
        for (int j = 0; j < numV-1; j++)
            printf("%d ", G[i][j]);
        printf("%d\n", G[i][numV-1]);
    }
    return 0;
}

void InsertVertex(int **G, int numV, int **newG, int v){
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            newG[i][j] = G[i][j];
    for (int i = 0; i < numV; i++){
        newG[v][i] = 0;
        newG[i][v] = 0;
    }
    for (int i = 0; i < v; i++)
        for (int j = v+1; j < numV; j++)
            newG[i][j] = G[i][j-1];
    for (int i = v+1; i < numV; i++)
        for (int j = 0; j < v; j++)
            newG[i][j] = G[i-1][j];
    for (int i = v+1; i < numV; i++)
        for (int j = v+1; j < numV; j++)
            newG[i][j] = G[i-1][j-1];
}

void InsertArc(int **G, int numV, int **newG, int v, int w){
    for (int i = 0; i < numV; i++)
        for (int j = 0; j < numV; j++)
            newG[i][j] = G[i][j];
    newG[v][w] = 1;
    newG[w][v] = 1;
}

void DeleteVertex(int **G, int numV, int **newG, int v){
    for (int i = 0; i < v; i++)
        for (int j = 0; j < v; j++)
            newG[i][j] = G[i][j];
    for (int i = 0; i < v; i++)
        for (int j = v + 1; j < numV+1; j++)
            newG[i][j - 1] = G[i][j];
    for (int i = v + 1; i < numV+1; i++)
        for (int j = 0; j < v; j++)
            newG[i - 1][j] = G[i][j];
    for (int i = v + 1; i < numV+1; i++)
        for (int j = v + 1; j < numV+1; j++)
            newG[i - 1][j - 1] = G[i][j];
}

void DeleteArc(int **G, int numV, int **newG, int v, int w){
    for (int i = 0; i < numV; i++)
        for (int j = 0; j < numV; j++)
            newG[i][j] = G[i][j];
    newG[v][w] = 0;
    newG[w][v] = 0;
}
