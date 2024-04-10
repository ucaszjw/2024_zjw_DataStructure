#include <stdio.h>
int compare(const void *a, const void *b){
    return (*(int*)b - *(int*)a);
}
int main(){
    int a[3];
    scanf("%d %d %d", &a[0], &a[1], &a[2]);
    qsort(a, 3, sizeof(int), compare);
    printf("%d %d %d", a[0], a[1], a[2]);
    return 0;
}