#include <stdio.h>
#include <stdlib.h>
struct lnode
{
    int data;
    struct lnode *next;
};

int main(){
    int m,n;
    scanf("%d %d",&m,&n);
    struct lnode *ha = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *hb = (struct lnode *)malloc(sizeof(struct lnode));
    struct lnode *pa = ha;
    struct lnode *pb = hb;
    for (int i = 0; i < m; i++)
    {
        scanf("%d",&pa->data);
        pa->next = (struct lnode *)malloc(sizeof(struct lnode));
        pa = pa->next;
    }
    pa->next = NULL;
    for (int i = 0; i < n-1; i++)
    {
        scanf("%d",&pb->data);
        pb->next = (struct lnode *)malloc(sizeof(struct lnode));
        pb = pb->next;
    }
    scanf("%d",&pb->data);
    pb->next = ha;
    pb = hb;
    while (pb->next != NULL)
    {
        printf("%d ",pb->data);
        pb = pb->next;
    }
    return 0;
}