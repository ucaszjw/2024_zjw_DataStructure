#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    int L[100];
    int R[100];
    int i = 0;
    do{
        scanf("%d", &L[i]);
        i++;
    } while ((getchar() != '\n'));
    i = 0;
    do{
        scanf("%d", &R[i]);
        i++;
    } while ((getchar() != '\n'));
    for (int j = 0; j < i-1; j++)
        printf("%d ", R[j]);
    printf("%d", R[i-1]);
    printf("\n");
    for (int j = 0; j < i-1; j++)
        printf("%d ", L[j]);
    printf("%d", L[i-1]);
    printf("\n");
    return 0;
}