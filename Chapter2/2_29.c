#include <stdio.h>
#include <stdlib.h>
struct lnode
{
    char data;
    struct lnode *next;
};

int main(){
    struct lnode* buildList();
    struct lnode* deleteNode(struct lnode *head, struct lnode *now);
    int find(struct lnode *h, char c);

    struct lnode *h = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *h1 = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *h2 = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *p = h;

    int data=0;
    h = buildList(); h1 = buildList(); h2 = buildList();
    p = h;
    while (p != NULL){
        if (find(h1,h->data) == 1 && find(h2,h->data) == 1){
            h = deleteNode(h,p);
            p = h;
        }
        else if (find(h1,p->data) == 0 || find(h2,p->data) == 0)
            p = p->next;
        else
            p = deleteNode(h,p);
    }
    p = h;
    while (p->next != NULL){
        printf("%c,",p->data);
        p = p->next;
    }
    printf("%c",p->data);
    return 0;
}

struct lnode* buildList(){
    struct lnode *h = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *p = h;
    char data,c;
    while ((c = getchar()) != '\n')
    {
        if (c == ',')
        {
            p->data = data;
            p->next = (struct lnode *)malloc(sizeof(struct lnode));
            p = p->next;
        }
        else
            data = c;
    }
    p->data = data;
    p->next = NULL;
    return h;
}

struct lnode* deleteNode(struct lnode *head, struct lnode *now){
    if (now != NULL){
        if (now == head){
            struct lnode *next = head->next;
            free(now);
            return next;
        }        
        else{
            struct lnode *p = head;
            while (p->next != now)
                p = p->next;
            p->next = now->next;
            free(now);
            return p->next;
        }
    }
    return NULL;
}

int find(struct lnode *h, char c){
    struct lnode *p = h;
    while (p != NULL){
        if (p->data == c)
            return 1;
        p = p->next;
    }
    return 0;
}