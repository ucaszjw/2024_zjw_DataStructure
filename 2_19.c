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
    int data=0,len=1;
    char c;
    while ((c = getchar()) != '\n')
    {
        if (c == ' ')
        {
            p->data = data;
            data = 0;
            p->next = (struct lnode *)malloc(sizeof(struct lnode));
            p = p->next;
            len++;
        }
        else
            data = data * 10 + c - '0';
    }
    p->data = data;
    p->next = NULL;
    p = head;
    
    int mink,maxk;
    scanf("%d %d",&mink,&maxk);
    while (head->data >= mink && head->data <= maxk){
        head = head->next;
        free(p);
        p = head;
    }

    struct lnode *q = p->next;
    while (q != NULL){
        if (q->data > mink && q->data < maxk){
            p->next = q->next;
            free(q);
            q = p->next;
        }
        else{
            p = p->next;
            q = q->next;
        }
    }    
    p = head;
    while (p != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    return 0;
}