#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Lnode
{
    char str[100];
    struct Lnode *next;
};

int main(){
    int tag;
    char buf[100], s[100];
    struct Lnode *head = (struct Lnode *)malloc(sizeof(struct Lnode));
    fgets(buf, 100, stdin);
    sscanf(buf, "%d %s", &tag, head->str);
    head->next = NULL;
    struct Lnode *p, *q;
    while (fgets(buf, 100, stdin) != NULL && buf[0] != '\n'){
        sscanf(buf, "%d %s", &tag, s);
        switch (tag)
        {
        case 1:
            p = head;
            q = (struct Lnode *)malloc(sizeof(struct Lnode));
            strcpy(q->str, s);
            while (p->next != NULL)
                p = p->next;
            p->next = q;
            q->next = NULL;
            break;
        case 2:
            p = head;
            if (strcmp(p->str, s) == 0){
                head = p->next;
                free(p);
                break;
            }
            while (p->next != NULL && strcmp(p->next->str, s) != 0)
                p = p->next;
            if (p->next == NULL)
                break;
            else{
                q = p->next;
                p->next = q->next;
                free(q);
                break;
            }
        case 3:
            p = head;
            if (strcmp(p->str, s) == 0){
                printf("%s\n", "True");
                break;
            }
            else {
                while (p->next != NULL && strcmp(p->next->str, s) != 0)
                    p = p->next;
                if (p->next == NULL)
                    printf("%s\n", "False");
                else
                    printf("%s\n", "True");
                break;
            }
        default:
            break;
        }
    }    
    return 0;
}