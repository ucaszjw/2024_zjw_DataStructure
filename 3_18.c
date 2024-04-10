#include <stdio.h>
int main(){
    char c;
    char arr[100];
    arr[0] = '$';
    int i = 1;
    while ((c = getchar()) != '\n' && arr[i] != '$'){
        if (c != '(' && c != ')')
            continue;
        if (c == '(')
            arr[i++] = c;            
        else if (c == ')')
            arr[--i] = ' ';
    }
    if (c == '\n' && arr[i-1] == '$')
        printf("1\n");
    else
        printf("0\n");
    return 0;    
}