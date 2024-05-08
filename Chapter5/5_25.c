#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void getArray(int *v);
int findData(int i, int j, int *v, int **matrix, int row, int col);
int main(){
    int m1,n1;
    scanf("%d %d", &m1, &n1);

    getchar();
    int v1[m1*n1];
    int v2[m1*n1];
    int v[m1*n1];
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
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++)
            scanf("%d", &matrix1[i][j]);
    getchar();
    getArray(v2);
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++)
            scanf("%d", &matrix2[i][j]);

    int data1, data2, count = 0;    
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++){
            if (matrix1[i][j] == 1 && matrix2[i][j] == 1){
                data1 = findData(i, j, v1, matrix1, m1, n1);
                data2 = findData(i, j, v2, matrix2, m1, n1);
                if (data1 + data2 == 0){
                    matrix[i][j] = 0;
                    continue;
                }
                matrix[i][j] = 1;
                v[count] = data1 + data2;
                count++;
            }
            else if (matrix1[i][j] == 1 && matrix2[i][j] == 0){
                matrix[i][j] = 1;
                v[count] = findData(i, j, v1, matrix1, m1, n1);
                count++;
            }
            else if (matrix1[i][j] == 0 && matrix2[i][j] == 1){
                matrix[i][j] = 1;
                v[count] = findData(i, j, v2, matrix2, m1, n1);
                count++;
            }
            else
                matrix[i][j] = 0;
        }

    int all_zero = 1;
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++)
            if (matrix[i][j] != 0) {
                all_zero = 0;
                break;
            }

    if (all_zero) {
        printf("\n");
    } else {
        // 否则，输出 v 数组
        for (int i = 0; i < count-1; i++)
            printf("%d ", v[i]);
        printf("%d\n", v[count-1]);
    }
    for (int i = 0; i < m1; i++){
        for (int j = 0; j < n1-1; j++)
            printf("%d ", matrix[i][j]);
        printf("%d\n", matrix[i][n1-1]);
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

int findData(int i, int j, int *v, int **matrix, int row, int col){
    int data, count = 0;
    for (int k = 0; k < i; k++)
        for (int l = 0; l < col; l++)
            if (matrix[k][l] == 1)
                count++;
    for (int l = 0; l < j; l++)
        if (matrix[i][l] == 1)
            count++;
    data = v[count];
    return data;
}