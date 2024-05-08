#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct lnode {
    int coeff;
    int exp;
    struct lnode *next;
};

void buildList(struct lnode *head);
void buildHead(struct lnode *head, int coeff, int exp);
void insertNode(struct lnode *head, int coeff, int exp);
void differentiate(struct lnode *head);
void bubbleSort(struct lnode *head);
void printList(struct lnode *head);

int main(){
    struct lnode *head = (struct lnode *)malloc(sizeof(struct lnode));
    buildList(head);
    differentiate(head);
    bubbleSort(head);
    printList(head);
    return 0;
}

// build a linked list to store the polynomial
void buildList(struct lnode *head){
    char c;
    int coeff=0, exp=0, sign=1, sign_e=1, isHead=1;
    while ((c=getchar()) != '\n' && c != EOF){
        if (c == ' '){
            continue;
        }
        if (c == '-'){
            sign = -1;
            continue;
        }
        if (c == '+'){
            sign = 1;
            continue;
        }
        if (c == 'x'){
            coeff = sign;
            if ((c=getchar()) == '^'){
                if ((c=getchar()) == '-'){
                    sign_e = -1;
                    while (isdigit((c=getchar())))
                        exp = exp*10 + (c-'0');
                    exp *= sign_e;
                    sign_e = 1;
                }
                else{
                    while (isdigit(c)){
                        exp = exp*10 + (c-'0');
                        c = getchar();
                    }
                    exp *= sign_e;
                    sign_e = 1;
                }
            }
            else
                exp = 1;
        }
        
        if (isdigit(c)){
            coeff = c-'0';
            while (isdigit(c=getchar()))
                coeff = coeff*10 + (c-'0');
            coeff *= sign;
            if (c == 'x'){
                if ((c=getchar()) == '^'){
                    if ((c=getchar()) == '-'){
                        sign_e = -1;
                        while (isdigit((c=getchar())))
                            exp = exp*10 + (c-'0');
                        exp *= sign_e;
                        sign_e = 1;
                    }
                    else{
                        while (isdigit(c)){
                            exp = exp*10 + (c-'0');
                            c = getchar();
                        }
                        exp *= sign_e;
                        sign_e = 1;
                    }
                }
                else
                    exp = 1;
            }
        }
        if (isHead){
            buildHead(head, coeff, exp);
            isHead = 0;
        }
        else
            insertNode(head, coeff, exp);
        coeff = 0;
        exp = 0;
        sign = 1;
    }
}

// build the head of the linked list
void buildHead(struct lnode *head, int coeff, int exp){
    head->coeff = coeff;
    head->exp = exp;
    head->next = NULL;
}

// insert a node to the linked list or add the coefficient to the existing node
void insertNode(struct lnode *head, int coeff, int exp){
    struct lnode *p = head;
    while (p != NULL){
        if (p->exp == exp){
            p->coeff += coeff;
            return;
        }
        p = p->next;
    }
    
    p = head;
    while (p->next != NULL){
        p = p->next;
    }
    struct lnode *newNode = (struct lnode *)malloc(sizeof(struct lnode));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    p->next = newNode;
}

// differentiate the polynomial
void differentiate(struct lnode *head){
    struct lnode *p = head;
    while (p != NULL){
        if (p->exp == 0){
            p->coeff = 0;
            p->exp = -1;
            p = p->next;
            continue;
        }
        p->coeff *= p->exp;
        p->exp--;
        p = p->next;
    }
}

// bubble sort the linked list by the exponent
void bubbleSort(struct lnode *head){
    struct lnode *p = head;
    if (p->next != NULL)
    {
        while (p != NULL){
            struct lnode *q = p->next;
            while (q != NULL){
                if (p->exp < q->exp){
                    int temp = p->exp;
                    p->exp = q->exp;
                    q->exp = temp;
                    temp = p->coeff;
                    p->coeff = q->coeff;
                    q->coeff = temp;
                }
                q = q->next;
            }
            p = p->next;
        }
    }
    else{
        return;
    }    
}

int abs(int a){
    return (a>=0)? a:-a;
}

// convert an integer to a string
char *itoa(int n){
    char *s = (char *)malloc(100*sizeof(char));
    int sign = 1;
    if (n < 0){
        n = -n;
        sign = -1;
    }
    int i = 0;
    while (n > 0){
        s[i] = n%10 + '0';
        n /= 10;
        i++;
    }
    if (sign == -1){
        s[i] = '-';
        i++;
    }
    s[i] = '\0';
    char temp;
    for (int j = 0; j < i/2; j++){
        temp = s[j];
        s[j] = s[i - j - 1];
        s[i - j - 1] = temp;
    }
    return s;
}

// print the linked list
void printList(struct lnode *head){
    struct lnode *p = head;
    while (p->coeff == 0){
        if (p->next == NULL){
            printf("0\n");
            return;
        }
        else{
            p = p->next;
        }        
    }
    
    printf("%s%s%s%s%s ", (p->coeff>=0)? "":"- ", (abs(p->coeff)==1 && p->exp!=0)? "":itoa(abs(p->coeff)), (p->exp==0)? "":"x", (p->exp==1 || p->exp==0)? "":"^", (p->exp==1)? "":itoa(p->exp));
    if (p->next == NULL){
        printf("\n");
        return;
    }
    p = p->next;
    while (p != NULL && p->coeff != 0){
        printf("%c %s%s%s%s ", (p->coeff>=0)? '+':'-', (abs(p->coeff)==1 && p->exp!=0)? "":itoa(abs(p->coeff)), (p->exp==0)? "":"x", (p->exp==1 || p->exp==0)? "":"^", (p->exp==1)? "":itoa(p->exp));
        p = p->next;
    }
}