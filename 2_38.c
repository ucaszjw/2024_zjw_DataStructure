#include <stdio.h>
#include <stdlib.h>
struct lnode
{
    int data;
    struct lnode *prior;
    struct lnode *next;
    int freq;
    int order;
};

int main(){
    void swap(struct lnode *now);
    int n;
    scanf("%d",&n);
    int d[n];
    for (int i = 0; i < n; i++)
        scanf("%d",&d[i]);
    struct lnode *head = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *p = head;
    for (int i = 0; i < n; i++){
        p->data = d[i];
        p->freq = 0;
        p->order = 0;
        if (i < n - 1) {
            p->next = (struct lnode *)malloc(sizeof(struct lnode));
            p->next->prior = p;
            p = p->next;
        }
    }
    p->next = head;
    head->prior = p;
        
    int data=0,order=1;
    char c;
    getchar();
    while ((c = getchar()) != '\n'){
        if (c == ' '){
            p = head;
            while (p->next != head){
                if (p->data == data){
                    p->freq++;
                    if (p->order == 0){
                        p->order = order;
                        order++;
                    }
                }
                p = p->next;
            }
            if (p->data == data){
                p->freq++;
                if (p->order == 0){
                    p->order = order;
                    order++;
                }
            }
            data = 0;
        }
        else
            data = data * 10 + c - '0';
    }
        
    p = head;
    do {
        if (p->data == data){
            p->freq++;
            if (p->order == 0){
                p->order = order;
            }
        }
        p = p->next;
    } while (p != head);  
    
    if (n == 2){
        if (p->freq > p->prior->freq || (p->freq == p->prior->freq && p->order < p->prior->order)){
            printf("%d %d", p->data, p->prior->data);
            return 0;
        }
        else{
            printf("%d %d", p->prior->data, p->data);
            return 0;
        }
    }

    p = head;
    struct lnode *tail = head->prior;
    int i;
    p = tail;
    while (1){
        i = 0;
        do {
            if (p->freq > p->prior->freq || (p->freq == p->prior->freq && p->order < p->prior->order)){
                if (p->prior == head)
                    head = p;                
                swap(p);
                i++;
            }
            else
                p = p->prior;
        } while (p != head);
        if (i == 0){
            break;
        }
        tail = head->prior;
        p = tail;
    }
    
    p = head;
    while (p->next != head){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("%d",p->data);    
    return 0;
}

void swap(struct lnode *now){
    struct lnode *p = now->prior;
    struct lnode *n = now->next;
    struct lnode *pp = p->prior;
    now->prior = pp;
    now->next = p;
    p->prior = now;
    p->next = n;
    pp->next = now;
    n->prior = p;
}