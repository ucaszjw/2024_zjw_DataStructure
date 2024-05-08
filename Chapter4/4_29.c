#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct string
{
    char chdata;
    struct string *next;
    struct string *succ;
};


int main(){
    int len_s, len_t;
    scanf("%d %d", &len_s, &len_t);
    getchar();
    struct string *head_s = (struct string *)malloc(sizeof(struct string));
    struct string *head_t = (struct string *)malloc(sizeof(struct string));
    head_s->chdata = '0';
    head_t->chdata = '0';
    struct string *p = head_s;
    for (int i = 0; i < len_s; i++){
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
        p->chdata = ch;
        p->succ = (struct string *)malloc(sizeof(struct string));
        p->succ->next = p;
        p = p->succ;
    }    
    p->succ = NULL;
    getchar();
    p = head_t;
    for (int i = 0; i < len_t; i++){
        char ch = getchar();
        if (ch == '\n') {
            break;
        }
        p->chdata = ch;
        p->succ = (struct string *)malloc(sizeof(struct string));
        p->succ->next = p;
        p = p->succ;
    }
    p->succ = NULL;

    p = head_s;
    int pos = 0;
    struct string *q = head_t;
    while (p->succ != NULL){
        if (p->chdata == q->chdata){
            q = q->succ;
            if (q->succ == NULL){
                printf("%d\n", pos - len_t + 1);
                return 0;
            }
        }
        else{
            q = head_t;
        }
        p = p->succ;
        pos++;
    }
    printf("-1\n");
    return 0;
}
