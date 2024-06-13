#include <stdio.h>

int main(){
    int k,m;
    scanf("%d %d", &k, &m);
    if (m < k-1)
    {
        printf("0\n");
        return 0;
    } else if (m == k-1)
    {
        printf("1\n");
        return 0;
    } else
    {
        int a[m+1];
        for (int i = 0; i < k-1; i++)
        {
            a[i] = 0;
        }
        a[k-1] = 1;
        for (int i = k; i < m+1; i++)
        {
            int sum = 0;
            for (int j = i-k; j < i; j++)
            {
                sum += a[j];
            }
            a[i] = sum;
        }
        printf("%d\n", a[m]);
        return 0;
    }
}