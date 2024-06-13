#include <stdio.h>

int main(){
    int row, col;
    scanf("%d %d", &row, &col);
    int matrix[row][col];
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    int min[row];
    for (int i = 0; i < row; i++){
        min[i] = matrix[i][0];
        for (int j = 0; j < col; j++){
            if (matrix[i][j] <= min[i]){
                min[i] = matrix[i][j];
            }
        }
    }
    for (int j = 0; j < col; j++){
        int max = matrix[0][j];
        for (int i = 0; i < row; i++){
            if (matrix[i][j] >= max){
                max = matrix[i][j];
            }
        }
        for (int i = 0; i < row; i++){
            if (matrix[i][j] == max && matrix[i][j] == min[i]){
                printf("%d ", matrix[i][j]);
            }
        }
    }
    return 0;
}