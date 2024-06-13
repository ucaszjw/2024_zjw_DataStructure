#include <stdio.h>
#include <stdlib.h>
#define M 16
struct Lnode
{
    int pos;
    struct Lnode *next;
};

int power(int x);
int buddy(int pos, int k);
int buddyAvailable(struct Lnode *A[], int k, int buddypos);
void merge(struct Lnode *A[], int k, int pos, int buddypos);
int main(){
    struct Lnode *A[M];
    int k, pos;
    char buf[100];
    for (int i = 0; i < M; i++){
        A[i] = (struct Lnode *)malloc(sizeof(struct Lnode));
        A[i]->next = NULL;
    }
    while (fgets(buf, sizeof(buf), stdin) != NULL && buf[0] != '\n'){
        k = buf[0] - '0';
        int i = 2;
        struct Lnode *p = A[k];
        while (buf[i] != '\n'){
            pos = 0;
            while (buf[i] != ' ' && buf[i] != '\n'){
                pos = pos * 10 + buf[i] - '0';
                i++;
            }
            struct Lnode *q = (struct Lnode *)malloc(sizeof(struct Lnode));
            q->pos = pos;
            q->next = p->next;
            p->next = q;
            p = q;
            if (buf[i] == '\n')
                break;
            i++;
        }
    }

    while (fgets(buf, sizeof(buf), stdin) != NULL && buf[0] != '\n'){
        k = buf[0] - '0';
        int i = 2;
        while (buf[i] != '\n'){
            pos = 0;
            while (buf[i] != ' ' && buf[i] != '\n'){
                pos = pos * 10 + buf[i] - '0';
                i++;
            }
            struct Lnode *p = A[k];
            if (A[k]->next == NULL){
                struct Lnode *q = (struct Lnode *)malloc(sizeof(struct Lnode));
                q->pos = pos;
                q->next = p->next;
                p->next = q;
                continue;
            }
            int buddypos = buddy(pos, k);
            if (buddyAvailable(A, k, buddypos))
                merge(A, k, pos, buddypos);
            else{
                struct Lnode *q = (struct Lnode *)malloc(sizeof(struct Lnode));
                q->pos = pos;
                while (p->next != NULL && p->next->pos < pos)
                    p = p->next;
                q->next = p->next;  
                p->next = q;
            }
        }    
    }
    
    for (int i = 0; i < M; i++){
        struct Lnode *p = A[i];
        if (p->next == NULL)
            continue;
        printf("%d ", i);
        while (p->next->next != NULL){
            printf("%d ", p->next->pos);
            p = p->next;
        }
        printf("%d\n", p->next->pos);
    }
    return 0;
}

int power(int x){
    int res = 1;
    for (int i = 0; i < x; i++)
        res *= 2;
    return res;
}

int buddy(int pos, int k){
    return (pos % power(k + 1) == 0) ? pos + power(k) : pos - power(k);
}

int buddyAvailable(struct Lnode *A[], int k, int buddypos){
    struct Lnode *p = A[k];
    while (p->next != NULL){
        if (p->next->pos == buddypos){
            struct Lnode *q = p->next;
            p->next = q->next;
            free(q);
            return 1;
        }
        p = p->next;
    }
    return 0;
}

void merge(struct Lnode *A[], int k, int pos, int buddypos){
    int mergepos = (pos < buddypos) ? pos : buddypos;
    if (buddyAvailable(A, k+1, buddy(mergepos, k+1)))
        merge(A, k+1, mergepos, buddy(mergepos, k+1));
    else{ 
        struct Lnode *p = A[k+1];
        struct Lnode *q = (struct Lnode *)malloc(sizeof(struct Lnode));
        q->pos = mergepos;
        while (p->next != NULL && p->next->pos < mergepos)
            p = p->next;
        q->next = p->next;
        p->next = q;
    }
}