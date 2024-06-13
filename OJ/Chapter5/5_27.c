#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct OLNode{
    int i,j;
    int e;
    struct OLNode *right, *down;
}OLNode, *OLink;
typedef struct{
    OLink *rhead, *chead;
    int mu, nu;
}CrossList;

void getArray(int *v);
void CreateMatrix(CrossList **M,int *v, int **matrix, int m, int n);
int Add(CrossList *A, CrossList *B, int **matrix, int *v, int m, int n);
int main(){
    int m1,n1;
    scanf("%d %d", &m1, &n1);
    getchar();
    int v1[m1*n1];
    int v2[m1*n1];
    int v[m1*n1];
    CrossList *A, *B, *C;
    int **matrix1;
    int **matrix2;
    int **matrix;
    matrix1 = (int **)malloc(m1*sizeof(int *));
    matrix2 = (int **)malloc(m1*sizeof(int *));
    matrix = (int **)malloc(m1*sizeof(int *));
    for (int i = 0; i < m1; i++){
        matrix1[i] = (int *)malloc(n1*sizeof(int));
        matrix2[i] = (int *)malloc(n1*sizeof(int));
        matrix[i] = (int *)malloc(n1*sizeof(int));
    }
    
    getArray(v1);
    CreateMatrix(&A, v1, matrix1, m1, n1);
    getchar();
    getArray(v2);
    CreateMatrix(&B, v2, matrix2, m1, n1);    
    int count = Add(A, B, matrix, v, m1, n1);

    if (count == 0)
        printf("\n");
    else{
        for (int i = 0; i < count-1; i++)
        {
            printf("%d ", v[i]);
        }
        printf("%d\n", v[count-1]);
    }
    for (int i = 0; i < m1; i++){
        for (int j = 0; j < n1-1; j++){
            printf("%d ", (matrix[i][j]==0)? 0:1);
        }
        printf("%d\n", (matrix[i][n1-1]==0)? 0:1);
    }
    return 0;
}

void getArray(int *v){
    char c;
    int sign = 1;
    *v = 0;
    while ((c = getchar()) != '\n'){
        if (c == ' '){
            *v *= sign;
            sign = 1;
            v++;
            *v = 0;
            continue;
        }
        if (c == '-'){
            sign = -1;
            continue;
        }
        if (isdigit(c)){
            *v = *v*10 + (c-'0');
        }
    }
    *v *= sign;
    v++;
    *v = 0;
}

void CreateMatrix(CrossList **M, int *v, int **matrix, int m, int n){
    *M = (CrossList *)malloc(sizeof(CrossList));
    (*M)->mu = m;
    (*M)->nu = n;
    (*M)->rhead = (OLink *)malloc(m*sizeof(OLink));
    (*M)->chead = (OLink *)malloc(n*sizeof(OLink));
    for (int i = 0; i < m; i++)
        (*M)->rhead[i] = NULL;
    for (int i = 0; i < n; i++)
        (*M)->chead[i] = NULL;
    
    int count = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 0)
                continue;
            else{
                matrix[i][j] = v[count];
                count++;
            }
            OLNode *p = (OLNode *)malloc(sizeof(OLNode));
            p->i = i;
            p->j = j;
            p->e = matrix[i][j];
            p->right = NULL;
            p->down = NULL;
            if ((*M)->rhead[i] == NULL)
                (*M)->rhead[i] = p;
            else{
                OLNode *q = (*M)->rhead[i];
                while (q->right != NULL)
                    q = q->right;
                q->right = p;
            }
            if ((*M)->chead[j] == NULL)
                (*M)->chead[j] = p;
            else{
                OLNode *q = (*M)->chead[j];
                while (q->down != NULL)
                    q = q->down;
                q->down = p;
            }
        }
    }            
}

int Add(CrossList *A, CrossList *B, int **matrix, int *v, int m, int n){
    int count = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            int sum = 0;
            if (A->rhead[i] != NULL && A->rhead[i]->j == j){
                sum += A->rhead[i]->e;
                A->rhead[i] = A->rhead[i]->right;
            }
            if (B->rhead[i] != NULL && B->rhead[i]->j == j){
                sum += B->rhead[i]->e;
                B->rhead[i] = B->rhead[i]->right;
            }
            matrix[i][j] = sum;
            if (sum == 0)
                continue;
            else{
                v[count] = sum;
                count++;
            }
        }
    }
    return count;
}