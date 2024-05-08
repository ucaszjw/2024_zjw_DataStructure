#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct string
{
    char chdata;
    int match;
    struct string *succ;
    struct string *next;
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
        p->match = 0;
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
        p = p->succ;
    }
    p->succ = NULL;

    p = head_s;
    int pos = 0, match = 0;
    struct string *q = head_t;
    struct string *mov = head_t;
    while (q->succ != NULL){
        if (p->chdata != q->chdata){
            q = head_t;
            match = 0;
            p->match = 0;
            pos++;
        }
        else if (p->chdata == q->chdata){
            p = p->succ;
            q = q->succ;
            match++;
            pos++;
            p->match = match;
        }
        if (match == len_t){
            printf("%d\n", pos - len_t);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}
