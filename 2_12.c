#include <stdio.h>

int main(){
    char a[100],b[100];
    int c,i=0,j=0;
    while ((c = getchar()) != '\n')
    {
        if (c == ',')
            i++;
        else
            a[i] = c;
    }
    a[i+1]='\0';
    i=0;
    while ((c = getchar()) != '\n')
    {
        if (c == ',')
            j++;
        else
            b[j] = c;
    }
    b[j+1]='\0';
    j=0;
    while (a[i]==b[j] && a[i]!='\0' && b[j]!='\0'){
        i++;
        j++;
    }
    if (a[i] == '\0' && b[j] == '\0')
        printf("0");
    else if (a[i] > b[j])
        printf("2");
    else
        printf("1");
    return 0;    
}