#include <stdio.h>
#include <stdlib.h>
struct Lnode
{
    int data;
    struct Lnode *next;
};


int main(){
    int x;
    struct Lnode *head1 = (struct Lnode *)malloc(sizeof(struct Lnode));
    struct Lnode *head2 = (struct Lnode *)malloc(sizeof(struct Lnode));
    struct Lnode *head3 = (struct Lnode *)malloc(sizeof(struct Lnode));
    head1 = head2 = head3 = NULL;
    do{
        scanf("%d", &x);
        if (x == 1){
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            new->data = x;
            if (head1 == NULL){
                head1 = new;
                head1->next = NULL;
            }
            else{
                new->next = head1->next;
                head1->next = new;
            }
        }
        else if (x == 2){
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            new->data = x;
            if (head2 == NULL){
                head2 = new;
                head2->next = NULL;
            }
            else{
                new->next = head2->next;
                head2->next = new;
            }
        }
        else if (x == 3){
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            new->data = x;
            if (head3 == NULL){
                head3 = new;
                head3->next = NULL;
            }
            else{
                new->next = head3->next;
                head3->next = new;
            }
        }
    } while ((getchar() != '\n'));
    struct Lnode *temp = head1;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    temp = head2;
    while (temp != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    temp = head3;
    while (temp->next != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
    return 0;
}