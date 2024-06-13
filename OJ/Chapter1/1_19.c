#include <stdio.h>

int fact(int n){
    if (n == 0)
    {
        return 1;
    }
    else
        return n*fact(n-1);
}

int power(int p){
    if (p == 0)
    {
        return 1;
    }
    else
        return 2*power(p-1);
}

int main(){
    int n,arrsize;
    scanf("%d %d", &n, &arrsize);
    if (n > arrsize || n > 10)
    {
        printf("-1\n");
        return 0;
    }
    else
    {
        int a[arrsize];
        for (int i = 0; i < arrsize; i++)
        {
            a[i] = fact(i)*power(i);
        }
        for (int i = 0; i < n; i++)
        {
            printf("%d ", a[i]);
        }
        return 0;
    }
}