#include <stdio.h>
#include <stdlib.h>

void swap(int *arr, int i, int j);
int main(){
    int len;
    scanf("%d", &len);
    int *arr = (int *)malloc(len * sizeof(int));
    for(int i = 0; i < len; i++)
        scanf("%d", &arr[i]);

    int not_sorted = 1;
    while (not_sorted){
        not_sorted = 0;
        for (int i = 0; i < len-1; i++){
            if (arr[i] > arr[i+1]){
                swap(arr, i, i+1);
                not_sorted = 1;
            }
        }
    }

    for (int i = 0; i < len-1; i++)
        printf("%d ", arr[i]);
    printf("%d\n", arr[len-1]);
    return 0;
}

void swap(int *arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}