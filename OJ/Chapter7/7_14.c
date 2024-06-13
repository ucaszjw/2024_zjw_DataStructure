#include <stdio.h>
#include <stdlib.h>

struct Vertex {
    int data;
    struct Vertex *next;
};

int main() {
    int numV, numE;
    scanf("%d,%d", &numV, &numE);
    getchar();

    struct Vertex *v[numV];
    for (int i = 0; i < numV; i++)
        v[i] = NULL;

    int vertex, edge, startAT1 = 0;
    for (int i = 0; i < numE; i++) {
        scanf("%d-%d,", &vertex, &edge);
        if (i == 0 && vertex == 1)
            startAT1 = 1;
        if (startAT1 == 1)
            vertex--;
        struct Vertex *new = (struct Vertex *)malloc(sizeof(struct Vertex));
        new->data = edge;
        new->next = NULL;
        struct Vertex *temp = v[vertex], *insert = v[vertex];
        if (insert == NULL) {
            v[vertex] = new;
            continue;
        }
        if (edge > insert->data) {
            new->next = insert;
            v[vertex] = new;
            continue;
        }
        if (temp->next == NULL && edge < temp->data) {
            temp->next = new;
            continue;
        }
     
        while (edge < temp->data && temp->next != NULL) 
            temp = temp->next;
        if (temp->next == NULL && edge < temp->data) {
            temp->next = new;
            continue;
        }
        while (insert->next != temp)
            insert = insert->next;
        insert->next = new;
        new->next = temp;
    }

    if (startAT1 == 0){
        for (int i = 0; i < numV; i++) {
            struct Vertex *temp = v[i];
            printf("%d%s", i,(temp == NULL) ? "" : " ");
            if (temp != NULL)
                printf("%d", temp->data);
            else{
                printf("\n");
                continue;
            }
            while (temp->next != NULL) {
                temp = temp->next;
                printf(",%d", temp->data);
            }
            printf("\n");
        }
    }
    else{
        for (int i = 0; i < numV; i++) {
            struct Vertex *temp = v[i];
            printf("%d%s", i+1,(temp == NULL) ? "" : " ");
            if (temp != NULL)
                printf("%d", temp->data);
            else{
                printf("\n");
                continue;
            }
            while (temp->next != NULL) {
                temp = temp->next;
                printf(",%d", temp->data);
            }
            printf("\n");
        }
    }
    return 0;
}