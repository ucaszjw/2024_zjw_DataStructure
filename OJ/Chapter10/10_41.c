#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b);
int main(){
    int *arr = (int *)malloc(1000 * sizeof(int));
    for (int i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, 1000, sizeof(int), compare);
    for (int i = 0; i < 1000; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}