#include <stdio.h>
#include <stdlib.h>
struct lnode
{
    int data;
    struct lnode *next;
    struct lnode *prior;
};

int main(){
    struct lnode *head = (struct lnode *)malloc(sizeof(struct lnode));
    scanf("%d", &head->data);
    struct lnode *tail = head;
    for (int i = 1; i < head->data; i++){
        struct lnode *q = (struct lnode *)malloc(sizeof(struct lnode));
        scanf("%d,", &q->data);
        tail->next = q;
        q->prior = tail;
        q->next = NULL;
        tail = q;
    }
    head->prior = tail;
    tail->next = head;
    struct lnode *p = tail->next->next;
    while (p != head){
        printf("%d,", p->data);
        p = p->next;
    }
    printf("%d", p->data);
    return 0;
}