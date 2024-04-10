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
    int data=0,len=1,sign=1;
    char c;
    while ((c = getchar()) != '\n'){
        if (c == ' '){
            p->data = sign*data;
            data = 0;
            sign = 1;
            p->next = (struct lnode *)malloc(sizeof(struct lnode));
            p = p->next;
            len++;
        }
        else if (c == '-'){
            sign = -1;
        }
        else if (c >= '0' && c <= '9'){
            data = data*10 + (c-'0');
        }
    }
    p->data = sign*data;
    p->next = NULL;
    
    p = head;
    int i;
    scanf("%d",&i);
    if (len == 1 && i == 0){
        printf("NULL");
        return 0;
    }
    if (i == 0){
        head = head->next;
        free(p);
        p = head;
        while (p->next != NULL){
            printf("%d ",p->data);
            p = p->next;
        }
        printf("%d",p->data);
        return 0;
    }
    for (int j = 0; j < i; j++)
        p = p->next;
    for (int j = 0; j < i-1; j++)
        q = q->next;
    q->next = p->next;
    free(p);
    q = head;
    while (q->next != NULL){
        printf("%d ",q->data);
        q = q->next;
    }
    printf("%d",q->data);
    return 0;
}