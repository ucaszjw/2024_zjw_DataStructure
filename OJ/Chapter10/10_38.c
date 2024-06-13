#include <stdio.h>
#include <stdlib.h>
struct Lnode
{
    int data;
    struct Lnode *next;
};
struct Lnode *H[64];

int Subsequence(struct Lnode *head);
void Mergesort(struct Lnode *H[], int n);
int main(){
    struct Lnode *head = NULL;
    int n, data;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%d", &data);
        if (head == NULL){
            head = (struct Lnode *)malloc(sizeof(struct Lnode));
            head->data = data;
            head->next = NULL;
        }
        else{
            struct Lnode *p = head;
            while (p->next != NULL)
                p = p->next;
            p->next = (struct Lnode *)malloc(sizeof(struct Lnode));
            p->next->data = data;
            p->next->next = NULL;
        }
    }
    int num = Subsequence(head);
    Mergesort(H, num);
    struct Lnode *p = H[0];
    while (p != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    return 0;
}

int Subsequence(struct Lnode *head){
    struct Lnode *p = head;
    for (int i = 0; i < 64; i++)
        H[i] = NULL;
    int i = 0;
    while (p->next != NULL){
        if (H[i] == NULL){
            H[i] = (struct Lnode *)malloc(sizeof(struct Lnode));
            H[i]->data = p->data;
            H[i]->next = NULL;
        }
        else{
            struct Lnode *q = H[i];
            while (q->next != NULL)
                q = q->next;
            q->next = (struct Lnode *)malloc(sizeof(struct Lnode));
            q->next->data = p->data;
            q->next->next = NULL;
        }
        if (p->data < p->next->data)
            p = p->next;
        else{
            i++;
            p = p->next;
        }
    }
    struct Lnode *q = head;
    while (q->next != p)
        q = q->next;
    if (q->data < p->data){
        struct Lnode *r = H[i];
        while (r->next != NULL)
            r = r->next;
        r->next = (struct Lnode *)malloc(sizeof(struct Lnode));
        r->next->data = p->data;
        r->next->next = NULL;
    }
    else{
        H[i] = (struct Lnode *)malloc(sizeof(struct Lnode));
        H[i]->data = p->data;
        H[i]->next = NULL;
    }
    return i;
}

void Mergesort(struct Lnode *H[], int n){
    struct Lnode *p = H[0];
    for (int i = 1; i <= n; i++){
        struct Lnode *q = H[i];
        struct Lnode *temp2 = q;
        struct Lnode *head = NULL;
        struct Lnode *r = head;
        while (p != NULL && q != NULL){
            if (p->data < q->data){
                if (head == NULL){
                    head = (struct Lnode *)malloc(sizeof(struct Lnode));
                    head->data = p->data;
                    head->next = NULL;
                    r = head;
                }
                else{
                    r->next = (struct Lnode *)malloc(sizeof(struct Lnode));
                    r->next->data = p->data;
                    r->next->next = NULL;
                    r = r->next;
                }
                p = p->next;
            }
            else{
                if (head == NULL){
                    head = (struct Lnode *)malloc(sizeof(struct Lnode));
                    head->data = q->data;
                    head->next = NULL;
                    r = head;
                }
                else{
                    r->next = (struct Lnode *)malloc(sizeof(struct Lnode));
                    r->next->data = q->data;
                    r->next->next = NULL;
                    r = r->next;
                }
                q = q->next;
            }
        }
        while (p != NULL){
            r->next = (struct Lnode *)malloc(sizeof(struct Lnode));
            r->next->data = p->data;
            r->next->next = NULL;
            p = p->next;
            r = r->next;
        }
        while (q != NULL){
            r->next = (struct Lnode *)malloc(sizeof(struct Lnode));
            r->next->data = q->data;
            r->next->next = NULL;
            q = q->next;
            r = r->next;
        }
        p = head;       
    }
    H[0] = p;
}