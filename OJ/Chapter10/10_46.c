#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b);
int main(){
    int len;
    scanf("%d", &len);
    int *arr = (int *)malloc(len * sizeof(int));
    for (int i = 0; i < len; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, len, sizeof(int), compare);
    for (int i = 0; i < len; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}