#include <stdio.h>
#include <stdlib.h>

int main(){
    int num = 0;
    int a[100];
    do{
        scanf("%d", &a[num++]);
    } while (getchar() != '\n');
    int *c = (int *)malloc(num * sizeof(int));
    for (int i = 0; i < num; i++){
        int less = 0;
        for (int j = 0; j < num; j++)
            if (a[j] < a[i])
                less++;
        c[i] = less;
    }
    for (int i = 0; i < num; i++)
        printf("%d ", c[i]);
    printf("\n");
    return 0;
}