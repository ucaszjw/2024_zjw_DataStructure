#include <stdio.h>

int main(){
    int row, col, row_begin, col_begin;
    enum direction {UP, DOWN, LEFT, RIGHT};
    enum direction dir;
    scanf("%d %d %d %d %d", &row, &col, &row_begin, &col_begin, &dir);
    int arr[row][col];
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            scanf("%d", &arr[i][j]);
            if (arr[i][j] == 1)
                arr[i][j] = 2;
        }
    }
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++)
            printf("%d", arr[i][j]);
        printf("\n");
    }
    return 0;
}