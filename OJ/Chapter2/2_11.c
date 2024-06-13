#include <stdio.h>

int main(){
    char c;
    int data=0,i=0,insert=0;
    int a[101]={0};
    while ((c = getchar()) != '\n')
    {
        if (c == ' ')
        {
            a[i] = data;
            data = 0;
            i++;
        }
        else
            data = data * 10 + c - '0';
    }
    a[i] = data;
    int max = i;
    scanf("%d",&insert);
    int j=0;
    for (; j < 101 && insert > a[j] && a[j] > 0; j++)
        ;
    while (i >= j){
        a[i+1] = a[i];
        i--;
    }    
    a[j] = insert;
    for (int j = 0; j <= max+1; j++)
        printf("%d ", a[j]);
    return 0;
}