#include <stdio.h>
#include <string.h>
int main(){
    char arr[100];
    arr[0] = '@';
    scanf("%s",arr+1);
    int i,j;
    int len = strlen(arr);
    if (len%2 == 0){
        i=len/2-1;
        j=i+1;
    }
    else{
        i=len/2-1;
        j=i+2;
    }
    while (i>=0 && arr[i--] == arr[j++] && arr[i] != '@' && arr[j] != '@')
        ;
    if (arr[i] == '@' && arr[j] == '@')
        printf("1\n");
    else
        printf("0\n");
    return 0;
}