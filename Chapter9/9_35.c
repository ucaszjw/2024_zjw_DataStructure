#include <stdio.h>
#include <stdlib.h>

int main(){
    int elem;
    struct Lnode{
        int data;
        struct Lnode *next;
    };
    scanf("%d", &elem);
    struct Lnode *head = (struct Lnode *)malloc(sizeof(struct Lnode));
    head->data = elem;
    head->next = NULL;
    struct Lnode *p = head;
    do{
        scanf("%d", &elem);
        struct Lnode *q = (struct Lnode *)malloc(sizeof(struct Lnode));
        q->data = elem;
        q->next = p->next;
        p->next = q;
        p = q;
    } while (getchar() != '\n');
    int low, high;
    scanf(" %d %d", &low, &high);
    p = head;
    while (p->next != NULL){
        if (p->next->data > low && p->next->data < high)
            printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}