#include <stdio.h>
#include <stdlib.h>
struct Lnode
{
    int data;
    struct Lnode *next;
};

int main(){
    int x;
    struct Lnode *head1 = NULL;
    struct Lnode *head2 = NULL;
    struct Lnode *tail;
    do{
        scanf("%d", &x);
        if (head1 == NULL){
            head1 = (struct Lnode *)malloc(sizeof(struct Lnode));
            head1->data = x;
            head1->next = NULL;
            tail = head1;
        }
        else{
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            new->data = x;
            new->next = NULL;
            tail->next = new;
            tail = new;
        }
    } while (getchar() != '\n');
    do{
        scanf("%d", &x);
        if (head2 == NULL){
            head2 = (struct Lnode *)malloc(sizeof(struct Lnode));
            head2->data = x;
            head2->next = NULL;
            tail = head2;
        }
        else{
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            new->data = x;
            new->next = NULL;
            tail->next = new;
            tail = new;
        }
    } while (getchar() != '\n');

    struct Lnode *temp1 = head1;
    struct Lnode *temp2 = head2;
    while (temp1 != NULL && temp2 != NULL){
        if (temp1->data < temp2->data){
            printf("%d ", temp1->data);
            temp1 = temp1->next;
        }
        else{
            printf("%d ", temp2->data);
            temp2 = temp2->next;
        }
    }
    while (temp1 != NULL){
        printf("%d ", temp1->data);
        temp1 = temp1->next;
    }
    while (temp2 != NULL){
        printf("%d ", temp2->data);
        temp2 = temp2->next;
    }    
    return 0;
}