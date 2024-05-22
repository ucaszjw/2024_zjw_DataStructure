#include <stdio.h>
#include <stdlib.h>
#define MAX 50
struct Block
{
    int tag;
    int start;
    int space;
    struct Block *next;
};

int isBehind(struct Block *B, struct Block *Ahead);
int isFront(struct Block *B, struct Block *Ahead);
int isPosition(struct Block *B, struct Block *Ahead);
int main(){
    struct Block *Ahead = (struct Block *)malloc(sizeof(struct Block));
    struct Block *Bhead = (struct Block *)malloc(sizeof(struct Block));
    struct Block *A = Ahead;
    struct Block *B = Bhead;
    int tag, start, space;
    int i = 0, j = 0, isAHead = 1, isBHead = 1;
    while (scanf(" %d %d %d", &tag, &start, &space) != EOF){
        if (!tag){
            if (isAHead){
                Ahead->tag = tag;
                Ahead->start = start;
                Ahead->space = space;
                Ahead->next = NULL;
                isAHead = 0;
            }else{
                A->next = (struct Block *)malloc(sizeof(struct Block));
                A = A->next;
                A->tag = tag;
                A->start = start;
                A->space = space;
                A->next = NULL;
            }
            i++;
        }
        else{
            if (isBHead){
                Bhead->tag = tag;
                Bhead->start = start;
                Bhead->space = space;
                Bhead->next = NULL;
                isBHead = 0;
            }else{
                B->next = (struct Block *)malloc(sizeof(struct Block));
                B = B->next;
                B->tag = tag;
                B->start = start;
                B->space = space;
                B->next = NULL;
            }
            j++;
        }
    }    

    int pos1, pos2, pos3;
    B = Bhead;
    for (int k = 0; k < j; k++)
    {
        pos1 = isBehind(B, Ahead);
        pos2 = isFront(B, Ahead);
        pos3 = isPosition(B, Ahead);
        if (pos1 >= 0){
            A = Ahead;
            for (int l = 0; l < pos1; l++)
                A = A->next;
            A->space += B->space;
        }
        else if (pos2 >= 0){
            A = Ahead;
            for (int l = 0; l < pos2; l++)
                A = A->next;
            A->space += B->space;
            A->start = B->start;
        }
        else if (pos3 >= 0){
            A = Ahead;
            for (int l = 0; l < pos3; l++)
                A = A->next;
            A->space += B->space;
        }
        
        else{
            struct Block *temp = (struct Block *)malloc(sizeof(struct Block));
            temp->tag = 0;
            temp->start = B->start;
            temp->space = B->space;
            A = Ahead;
            while (A->next != NULL && A->next->start < B->start)
                A = A->next;
            temp->next = A->next;
            A->next = temp;
        }
        B = B->next;
    }

    A = Ahead;
    while (A->next != NULL){
        if (A->start + A->space == A->next->start){
            A->space += A->next->space;
            A->next = A->next->next;
            struct Block *temp = A->next;
            free(temp);
        }
        else if (A->start == A->next->start){
            A->space = (A->space > A->next->space) ? A->space : A->next->space;
            struct Block *temp = A->next;
            A->next = A->next->next;
            free(temp);
        }
        else
            A = A->next;
    }
    
    
    while (Ahead != NULL){
        printf("%d %d %d\n", Ahead->tag, Ahead->start, Ahead->space);
        Ahead = Ahead->next;
    }    
    return 0;
}

int isBehind(struct Block *B, struct Block *Ahead){
    struct Block *A = Ahead;
    int pos = 0;
    while (A != NULL){
        if (B->start == A->start + A->space)
            return pos;
        A = A->next;
        pos++;
    }
    return -1;
}

int isFront(struct Block *B, struct Block *Ahead){
    struct Block *A = Ahead;
    int pos = 0;
    while (A != NULL){
        if (B->start + B->space == A->start)
            return pos;
        A = A->next;
        pos++;
    }
    return -1;
}

int isPosition(struct Block *B, struct Block *Ahead){
    struct Block *A = Ahead;
    int pos = 0;
    while (A != NULL){
        if (B->start == A->start)
            return pos;
        A = A->next;
        pos++;
    }
    return -1;
}