#include <stdio.h>
#include <stdlib.h>
struct lnode
{
    int data;
    struct lnode *next;
};

int main(){
    struct lnode *head = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *p = head;
    struct lnode *q = head;
    int data=0,len=0;
    int i;
    while (scanf("%d",&data) != EOF){
        p->data = data;
        p->next = (struct lnode *)malloc(sizeof(struct lnode));
        p = p->next;
        len++;
    }
    p = NULL;
    
    p = head;
    while (p->next != NULL){
        p = p->next;
    }
    i = p->data;
    struct lnode *r = p;

    p = head;
    if (len == 2 && i == 0){
        printf("NULL");
        return 0;
    }
    if (i == 0){
        head = head->next;
        free(p);
        p = head;
        while (p->next != r){
            printf("%d ",p->data);
            p = p->next;
        }
        return 0;
    }
    for (int j = 0; j < i; j++)
        p = p->next;
    for (int j = 0; j < i-1; j++)
        q = q->next;
    q->next = p->next;
    free(p);
    q = head;
    while (q->next != r){
        printf("%d ",q->data);
        q = q->next;
    }
    return 0;
}