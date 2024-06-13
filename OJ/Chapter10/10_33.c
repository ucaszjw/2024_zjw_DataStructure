#include <stdio.h>
#include <stdlib.h>
struct Lnode
{
    int data;
    struct Lnode *next;
};

int main(){
    int x;
    struct Lnode *head = (struct Lnode *)malloc(sizeof(struct Lnode));
    head = NULL;
    do{
        scanf("%d", &x);
        if (head == NULL){
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            new->data = x;
            new->next = NULL;
            head = new;
        }
        else{
            struct Lnode *new = (struct Lnode *)malloc(sizeof(struct Lnode));
            struct Lnode *temp = head;
            new->data = x;
            new->next = NULL;
            while (temp->next != NULL){
                temp = temp->next;
            }
            temp->next = new;
        }
    } while ((getchar() != '\n'));
    
    struct Lnode *unsorted = head;
    while (unsorted->next != NULL){
        struct Lnode *min = unsorted;
        struct Lnode *temp = unsorted->next;
        while (temp != NULL){
            if (temp->data < min->data){
                min = temp;
            }
            temp = temp->next;
        }
        int t = unsorted->data;
        unsorted->data = min->data;
        min->data = t;
        unsorted = unsorted->next;
    }

    struct Lnode *temp = head;
    while (temp->next != NULL){
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n", temp->data);
    return 0;
}