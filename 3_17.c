#include <stdio.h>
int main(){
    char c;
    char arr[100];
    arr[0] = '&';
    int i = 1;
    while ((c = getchar()) != '\n' && c != '&')
        arr[i++] = c;
    i--;
    while (arr[i--] == (c = getchar()))
        ;
    if (c == '@' && arr[i+1] == '&')
        printf("1\n");
    else
        printf("0\n");
    return 0;
}