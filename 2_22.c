#include <stdio.h>
#include <stdlib.h>
struct lnode
{
    char data;
    struct lnode *next;
};

int main(){
    char c;
    struct lnode *head = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *p = head;
    while ((c=getchar()) != '\n'){
        if (c == ',')
        {
            p->next = (struct lnode *)malloc(sizeof(struct lnode));
            p = p->next;
        }
        else
            p->data = c;
    }
    p->next = NULL;
    struct lnode *q = NULL;
    struct lnode *r = head;
    while (r != NULL){
        struct lnode *next = r->next;
        r->next = q;
        q = r;
        r = next;
    }
    while (q->next != NULL){
        printf("%c,",q->data);
        q = q->next;
    }
    printf("%c",q->data);
    return 0;
}