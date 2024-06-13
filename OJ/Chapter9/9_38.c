#include <stdio.h>

int compare(const void *a, const void *b);
int main(){
    int A[100];
    int elem, i = 0;
    do
    {
        scanf("%d", &elem);
        if (elem > 0)
            A[i++] = elem;
    } while (getchar() != '\n');
    do
    {
        scanf("%d", &elem);
        if (elem > 0)
            A[i++] = elem;
    } while (getchar() != '\n');
    qsort(A, i, sizeof(int), compare);
    for (int j = 0; j < i-1; j++)
        printf("%d ", A[j]);
    printf("%d\n", A[i-1]);
    return 0;
}

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}