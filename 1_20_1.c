#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, x_0;
    scanf("%d %d", &n, &x_0);
    int *p = (int *)malloc((n+1) * sizeof(int));
    for (int i = 0; i < n+1; i++)
        scanf("%d", &p[i]);
    int result = p[n];
    for (int i = n - 1; i >= 0; i--)
        result = result * x_0 + p[i];
    printf("%d", result);
    free(p);
    return 0;
}