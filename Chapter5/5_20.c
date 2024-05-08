#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* itoa(int n);
int main(){
    int row, col;
    scanf("%d %d", &row, &col);
    int matrix[row][col];
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    int isHead=1;
    for (int i = row-1; i >= 0; i--){
        for (int j = col-1; j >= 0; j--){
            if (matrix[i][j] == 0)
                continue;
            printf("%s%s%s%s%s%s%s%s", (isHead==1)? "":"+", (matrix[i][j]==0 || matrix[i][j]==1)? "":itoa(matrix[i][j]), (matrix[i][j]==0 || i==0)? "":"x", (matrix[i][j]==0 || i==0)? "":"E", (matrix[i][j]==0 || i==0)? "":itoa(i), (matrix[i][j]==0 || j==0)? "":"y", (matrix[i][j]==0 || j==0)? "":"E", (matrix[i][j]==0 || j==0)? "":itoa(j));
            isHead = 0;
        }
    }
    return 0;
}

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
